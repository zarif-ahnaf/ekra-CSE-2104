# Rebuild every Drawings/Codes.odt from the INTACT source .cpp files.
# - prettify code with clang-format (LLVM, 4-space, 100-col)
# - highlight with the Code Highlighter 2 plugin's bundled Pygments (C++ "default")
# - JetBrains Mono for all code
# - embed the salvaged real-terminal PNG(s) per program
# - restored Problem Statement / Input text
import os, sys, subprocess, re

PP = r"C:\Users\zarif\AppData\Roaming\LibreOffice\4\user\uno_packages\cache\uno_packages\lu66442x0dtv.tmp_\codehighlighter2.oxt\python\pythonpath"
sys.path.insert(0, PP)
from pygments.lexers import get_lexer_by_name
from pygments.styles import get_style_by_name

from odf.opendocument import OpenDocumentText
from odf.style import Style, TextProperties
from odf.text import H, P, Span
from odf.draw import Frame, Image

LEX = get_lexer_by_name("c++", stripnl=False)
STY = get_style_by_name("default")
FONT = "JetBrains Mono"
ROOT = "D:/Programming/ekra"
CF = r"C:\Users\zarif\AppData\Local\Programs\Python\Python315\Scripts\clang-format.exe"
CFG = r"C:\Users\zarif\AppData\Local\Programs\Python\Python315\Lib\site-packages\clang_format\defaults\LLVM"

# day -> list of programs; each program: (cpp_file, problem, input_lines, png_filename)
CAP = r"C:\Users\zarif\ekra_capture"
DATA = {
    1: [
        ("code.cpp",
         "Build a Daraz-style shopping system: store user and order details in a class, compute a 4% discount capped by a coin value, and calculate the final payable amount for either Cash-on-Delivery or an online payment method with an extra payment discount.",
         ["01712345678  ekra  pass123  ekra@gmail.com",
          "5000  500  100  20",
          "1"],
         "NEW_D1.png"),
    ],
    2: [
        ("code.cpp",
         "Implement an Employee Attendance System as a single Employee class. The class captures employee details, a fixed working window, and 30 days of entry/leave stamps (read from the system clock). It computes per-day work hours, weekly overtime, a 10% bonus, and deductions for late entries / early leaves, then prints the full attendance record and a final salary breakdown.",
         ["101", "Payel Akter Ekra", "50000", "50000",
          "9", "30", "17", "0"],
         "NEW_D2.png"),
    ],
    3: [
        ("code.cpp",
         "Model employee salaries using a class with static data members that accumulate total pay per role, a constructor that sets them, and a destructor that prints the totals and reports which role has the highest total salary.",
         ["(no input)"],
         "NEW_D3.png"),
    ],
    4: [
        ("code.cpp",
         "Maintain an array of Bag objects with a static count of created bags. Provide a static member function to print the total, and two friend functions that inspect the private data to report the most-sold size and the most expensive bag.",
         ["(10 bags, each with name, size, price)"],
         "NEW_D4.png"),
    ],
    5: [
        ("code.cpp",
         "Use single inheritance from a base 'shape' class: a 'volume' derived class and an 'Area' derived class each compute volume / surface area for a Cube, Cylinder and Box from shared dimension data.",
         ["(no input)"],
         "NEW_D5a.png"),
        ("code_2.cpp",
         "Use multi-level inheritance (root -> calculation -> decision -> root_calculation) to compute the discriminant of a quadratic equation, state whether the roots are real or complex, and print the two roots for a = 2, b = 5, c = 3.",
         ["(no input)"],
         "NEW_D5b.png"),
    ],
    6: [
        ("code.cpp",
         "Combine several work/energy calculation classes (force-displacement, power-time, angle-force, kinetic, gravitational, elastic, thermodynamic, rotational) into a single class using multiple inheritance, compute each value, and report which is the greatest.",
         ["(no input)"],
         "NEW_D6a.png"),
        ("code_2.cpp",
         "Demonstrate the diamond problem and its solution with virtual inheritance: base A is inherited virtually by B and C, and D inherits from both. Show that D holds a single shared copy of A and can display x, y and their sum.",
         ["(no input)"],
         "NEW_D6b.png"),
    ],
    7: [
        ("code.cpp",
         "Overload the '+' and '==' operators for a Point class and overload a 'move' member for a Snake class; run a short loop that uses the overloaded operators to score moves and decrement a life counter until game over.",
         ["(no input)"],
         "NEW_D7.png"),
    ],
    8: [
        ("code.cpp",
         "Define an abstract 'Payment' base class with a pure virtual function and concrete derived payment classes that override it, then dispatch the correct payment computation from a common base-class pointer.",
         ["(no input)"],
         "NEW_D8.png"),
    ],
    9: [
        ("code.cpp",
         "Use try/catch to detect and report a negative number entered by the user, throwing a custom exception when the value is below zero.",
         ["-5"],
         "NEW_D9a.png"),
        ("code_2.cpp",
         "Write a header line and the numbers 39 through 72 into a text file using an ofstream, then read them back and print them.",
         ["(no input)"],
         "NEW_D9b.png"),
        ("code_3.cpp",
         "Read integers from CSE21.txt using an ifstream and print each one with its position.",
         ["(no input)"],
         "NEW_D9c.png"),
        ("code_4.cpp",
         "Read integers from Shagor.txt, print each one, and report the total count of values read.",
         ["(no input)"],
         "NEW_D9d.png"),
    ],
}


def prettify(path):
    src = open(path, "r", encoding="utf-8", errors="replace").read()
    try:
        out = subprocess.run(
            [CF, "--style=file:" + CFG, "--assume-filename=x.cpp"],
            input=src, capture_output=True, text=True, timeout=60)
        if out.returncode == 0 and out.stdout.strip():
            return out.stdout
    except Exception:
        pass
    return src


def build(outpath, progs):
    doc = OpenDocumentText()
    for nm, sz, fw in [("LabH1", "13pt", "bold"), ("LabLabel", "10pt", "bold"), ("LabBody", "10pt", None)]:
        s = Style(name=nm, family="paragraph")
        tp = {"fontsize": sz, "fontname": "Calibri"}
        if fw:
            tp["fontweight"] = fw
        s.addElement(TextProperties(**tp))
        doc.styles.addElement(s)

    root = Style(name="CH2", family="text")
    root.addElement(TextProperties(fontname=FONT, fontsize="9pt", fontfamily="monospace"))
    doc.styles.addElement(root)

    cache = {}
    def token_style(tt):
        key = str(tt)
        if key in cache:
            return cache[key]
        s = STY.style_for_token(tt)
        col = s.get("color")
        name = "ch2_" + re.sub(r"[^a-z0-9]", "", key.lower())
        st = Style(name=name, family="text", parentstylename="CH2")
        tp = {}
        if col:
            tp["color"] = "#" + col
        if s.get("bold"):
            tp["fontweight"] = "bold"
        if s.get("italic"):
            tp["fontstyle"] = "italic"
        if s.get("underline"):
            tp["textunderline"] = "single"
        if tp:
            st.addElement(TextProperties(**tp))
        doc.styles.addElement(st)
        cache[key] = name
        return name

    def h(text):
        e = H(outlinelevel=1)
        span = Span(stylename="LabH1"); span.addText(text); e.addElement(span)
        doc.text.addElement(e)

    def ap(style, text):
        p = P(stylename=style); p.addText(text); doc.text.addElement(p)

    def code_line(line):
        p = P(); doc.text.addElement(p)
        toks = LEX.get_tokens(line)
        for tt, tv in toks:
            sp = Span(stylename=token_style(tt)); sp.addText(tv); p.addElement(sp)

    for i, (fn, problem, inputs, png) in enumerate(progs, start=1):
        title = f"Program {i}" if len(progs) > 1 else "Program 1"
        h(title)
        ap("LabLabel", "Problem Statement")
        ap("LabBody", problem)
        ap("LabBody", "")
        ap("LabLabel", "Source Code:")
        # outpath is ROOT/Day D/Drawings/Codes.odt -> dpath = ROOT/Day D
        dpath = os.path.dirname(os.path.dirname(outpath))
        cfile = os.path.join(dpath, "In Lab", fn)
        for ln in prettify(cfile).split("\n"):
            code_line(ln + "\n")
        ap("LabLabel", "Input:")
        for ln in inputs:
            code_line(ln + "\n")
        ap("LabBody", "")
        ap("LabLabel", "Output (Windows Terminal):")
        pngpath = os.path.join(CAP, png)
        if os.path.exists(pngpath):
            with open(pngpath, "rb") as f:
                blob = f.read()
            mf = doc.addPicture(f"Pictures/{png}", mediatype="image/png", content=blob)
            fr = Frame(width="16cm", height="11cm", anchortype="as-char")
            fr.addElement(Image(href=mf))
            doc.text.addElement(fr)
        ap("LabBody", "")
    doc.save(outpath)


if __name__ == "__main__":
    total = 0
    for d, progs in DATA.items():
        out = os.path.join(ROOT, f"Day {d}", "Drawings", "Codes.odt")
        os.makedirs(os.path.dirname(out), exist_ok=True)
        build(out, progs)
        total += len(progs)
        print(f"Day {d}: {len(progs)} program(s) -> {out}")
    print(f"TOTAL programs built: {total}")
