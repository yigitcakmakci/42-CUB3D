#!/usr/bin/env python3
"""
norm_fix.py - Automates the MECHANICAL norminette fixes only.

What it DOES fix (safe, whitespace-only):
  - Leading 4-space indentation  -> tabs
  - Trailing whitespace          -> removed  (SPACE_EMPTY_LINE / SPC_BEFORE_NL)
  - 2+ consecutive blank lines    -> single blank line
  - Blank line(s) at end of file  -> single trailing newline (EMPTY_LINE_EOF)
  - Missing 42 header             -> inserted (template from ft_atoi.c)

What it does NOT (and CANNOT) fix - do these by hand:
  - TOO_MANY_FUNCS / TOO_MANY_LINES / TOO_MANY_ARGS / TOO_MANY_VARS_FUNC
  - FORBIDDEN_CS  (for-loops -> while)
  - FORBIDDEN_CHAR_NAME  (xStart, key_W, ... -> lowercase/underscore)
  - DECL_ASSIGN_LINE  (int x = ...;  -> split declaration and assignment)
  - MISALIGNED_VAR_DECL  (needs a tab between type and name)

Usage:
  python3 scripts/norm_fix.py                 # fixes src/*.c src/*.h
  python3 scripts/norm_fix.py src/render.c    # fixes given files
  python3 scripts/norm_fix.py --check         # just run norminette, no edits

Backups (.bak) are written next to each file before editing.
COMMIT YOUR WORK FIRST.
"""
import glob
import os
import re
import subprocess
import sys

# Recognised C type starters for a declaration line (order matters: longest
# alternatives first so "unsigned int" wins over "unsigned").
TYPE_RE = (
    r"(?:unsigned\s+int|unsigned\s+char|unsigned\s+long|unsigned|const\s+char"
    r"|struct\s+\w+|void|char|short|int|long|float|double|size_t|ssize_t"
    r"|t_\w+)"
)
# leading tabs, a type, a whitespace gap, then the rest (name / *name / proto).
DECL_RE = re.compile(r"^(\t*)(" + TYPE_RE + r")([ \t]+)(\*?[A-Za-z_].*)$")
# struct/union/enum close line:  "} t_name;"  ->  "}\tt_name;"
CLOSE_RE = re.compile(r"^\}[ \t]+(t_\w+.*;)$")

# 42 header copied verbatim from a norm-valid file (include/libft/ft_atoi.c).
# Only line index 3 (the filename line) is regenerated per file.
HEADER = [
    "/* ************************************************************************** */",
    "/*                                                                            */",
    "/*                                                        :::      ::::::::   */",
    "/*   {filename}                                          :+:      :+:    :+:   */",
    "/*                                                    +:+ +:+         +:+     */",
    "/*   By: alozpola <alozpola@student.42kocaeli.co    +#+  +:+       +#+        */",
    "/*                                                +#+#+#+#+#+   +#+           */",
    "/*   Created: 2025/05/28 16:32:22 by alozpola          #+#    #+#             */",
    "/*   Updated: 2025/06/19 22:55:26 by alozpola         ###   ########.fr       */",
    "/*                                                                            */",
    "/* ************************************************************************** */",
]


def build_header(path):
    """Return the 11-line 42 header for this file, correctly padded."""
    name = os.path.basename(path)
    # prefix "/*   " (5) + name padded to 51 + suffix (24) = 80 columns
    line4 = "/*   " + name.ljust(51) + ":+:      :+:    :+:   */"
    lines = list(HEADER)
    lines[3] = line4
    return "\n".join(lines) + "\n\n"


def has_header(text):
    return text.startswith("/* ***")


def fix_leading_indent(line):
    """Convert leading indentation to tabs (4 spaces = 1 tab)."""
    i = 0
    col = 0
    while i < len(line) and line[i] in " \t":
        if line[i] == "\t":
            col += 4 - (col % 4)
        else:
            col += 1
        i += 1
    rest = line[i:]
    tabs = col // 4
    spaces = col % 4
    return "\t" * tabs + " " * spaces + rest


def _match_decl(line):
    """Return (indent, type, rest) if line is a declaration, else None."""
    m = DECL_RE.match(line)
    if not m:
        return None
    indent, typ, _gap, rest = m.group(1), m.group(2), m.group(3), m.group(4)
    # Skip things that are clearly not declarations (control flow keywords are
    # already excluded by TYPE_RE, but guard against multiplication like "int
    # * something" used as an expression is rare in norm code, so we keep it).
    return (indent, typ, rest)


def align_declarations(lines):
    """Align consecutive declaration lines: type -> name separated by tabs,
    every name landing on the same tab stop within the block."""
    out = []
    i = 0
    n = len(lines)
    while i < n:
        block = []
        while i < n:
            d = _match_decl(lines[i])
            if d is None:
                break
            block.append(d)
            i += 1
        if not block:
            out.append(lines[i])
            i += 1
            continue
        # only align lines that share the same indentation depth
        indent = block[0][0]
        if any(b[0] != indent for b in block):
            groups = _split_by_indent(block)
        else:
            groups = [block]
        for grp in groups:
            target = max(len(b[1]) // 4 + 1 for b in grp)
            for ind, typ, rest in grp:
                tabs = target - len(typ) // 4
                out.append(ind + typ + "\t" * tabs + rest)
    return out


def _split_by_indent(block):
    groups = []
    cur = []
    depth = None
    for b in block:
        if depth is None or b[0] == depth:
            cur.append(b)
            depth = b[0]
        else:
            groups.append(cur)
            cur = [b]
            depth = b[0]
    if cur:
        groups.append(cur)
    return groups


def fix_text(text):
    lines = text.split("\n")
    out = []
    blank_run = 0
    for line in lines:
        line = fix_leading_indent(line)
        line = line.rstrip(" \t")          # trailing whitespace / empty-line spaces
        line = CLOSE_RE.sub(r"}\t\1", line)  # "} t_name;" -> "}\tt_name;"
        if line == "":
            blank_run += 1
            if blank_run >= 2:             # collapse consecutive blanks
                continue
        else:
            blank_run = 0
        out.append(line)
    out = align_declarations(out)
    # strip trailing blank lines, guarantee exactly one final newline
    while out and out[-1] == "":
        out.pop()
    return "\n".join(out) + "\n"


def process(path):
    with open(path, "r") as f:
        text = f.read()
    original = text
    if not has_header(text):
        text = build_header(path) + text
    text = fix_text(text)
    if text == original:
        print("  unchanged: %s" % path)
        return
    if not os.path.exists(path + ".bak"):
        with open(path + ".bak", "w") as f:
            f.write(original)
    with open(path, "w") as f:
        f.write(text)
    print("  fixed:     %s  (backup: %s.bak)" % (path, path))


def run_norminette(files):
    print("\n=== norminette summary ===")
    try:
        res = subprocess.run(["norminette"] + files,
                             capture_output=True, text=True)
    except FileNotFoundError:
        print("norminette not found in PATH.")
        return
    errors = re.findall(r"^Error: (\w+)", res.stdout, re.M)
    if not errors:
        print("No errors. All good!")
        return
    counts = {}
    for e in errors:
        counts[e] = counts.get(e, 0) + 1
    for name, n in sorted(counts.items(), key=lambda x: -x[1]):
        print("  %4d  %s" % (n, name))
    print("  total: %d" % len(errors))


def main():
    args = [a for a in sys.argv[1:] if a != "--check"]
    check_only = "--check" in sys.argv[1:]
    if args:
        files = args
    else:
        files = sorted(glob.glob("src/*.c") + glob.glob("src/*.h"))
    if not files:
        print("No files to process.")
        return
    if not check_only:
        print("Applying mechanical fixes:")
        for path in files:
            process(path)
    run_norminette(files)


if __name__ == "__main__":
    main()
