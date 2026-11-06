# Regenerate every Codes.odt with Code Highlighter 2 styling:
# each code line tokenized by the plugin's own Pygments (C++ lexer, "default" style),
# rendered as colored JetBrains-Mono spans. Preserves problem statements, inputs, PNGs.
import os, sys, re, zipfile

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


def parse(oxpath):
    z = zipfile.ZipFile(oxpath)
    xml = z.read("content.xml").decode("utf-8")
    pics = {n: z.read(n) for n in z.namelist() if n.startswith("Pictures/")}
    body = xml.split("<office:text>", 1)[1].split("</office:text>", 1)[0]
    programs = []
    headers = list(re.finditer(r'<text:h text:outline-level="1"><text:span text:style-name="LabH1">([^<]*)</text:span></text:h>', body))
    bounds = [h.start() for h in headers] + [len(body)]
    for i, h in enumerate(headers):
        seg = body[h.end():bounds[i + 1]]
        ps = re.search(r'<text:p text:style-name="LabBody">([^<]*)</text:p>', seg)
        problem = ps.group(1) if ps else ""
        src = re.search(r'Source Code:</text:p>(.*?)<text:p text:style-name="LabLabel">Input:', seg, re.S)
        code_block = src.group(1) if src else ""
        inp = re.search(r'Input:</text:p>(.*?)<text:p text:style-name="LabLabel">Output', seg, re.S)
        input_block = inp.group(1) if inp else ""
        png = re.search(r'xlink:href="(Pictures/[^"]+)"', seg)
        code = [unesc(l) for l in re.findall(r'<text:p text:style-name="LabCode">([^<]*)</text:p>', code_block)]
        inputs = [unesc(l) for l in re.findall(r'<text:p text:style-name="LabCode">([^<]*)</text:p>', input_block)]
        programs.append(dict(title=h.group(1), problem=problem, code=code, inputs=inputs, png=png.group(1) if png else None))
    return programs, pics


def unesc(s):
    return (s.replace("&lt;", "<").replace("&gt;", ">")
             .replace("&quot;", '"').replace("&amp;", "&").replace("&#10;", "\n"))


def build(outpath, programs, pics):
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
        col = STY.style_for_token(tt).get("color") or None
        s = STY.style_for_token(tt)
        name = "ch2_" + re.sub(r"[^a-z0-9]", "", tt.__str__().lower())
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
        for tt, tv in LEX.get_tokens(line):
            sp = Span(stylename=token_style(tt)); sp.addText(tv); p.addElement(sp)

    for prog in programs:
        h(prog["title"])
        ap("LabLabel", "Problem Statement")
        ap("LabBody", prog["problem"])
        ap("LabBody", "")
        ap("LabLabel", "Source Code:")
        for ln in prog["code"]:
            code_line(ln)
        ap("LabLabel", "Input:")
        for ln in prog["inputs"]:
            code_line(ln)
        ap("LabBody", "")
        ap("LabLabel", "Output (Windows Terminal):")
        if prog["png"] and prog["png"] in pics:
            mf = doc.addPicture(prog["png"], mediatype="image/png", content=pics[prog["png"]])
            fr = Frame(width="16cm", height="11cm", anchortype="as-char")
            fr.addElement(Image(href=mf))
            doc.text.addElement(fr)
        ap("LabBody", "")
    doc.save(outpath)


if __name__ == "__main__":
    for d in range(1, 10):
        oxt = f"{ROOT}/Day {d}/Drawings/Codes.odt"
        if not os.path.exists(oxt):
            continue
        programs, pics = parse(oxt)
        build(oxt, programs, pics)
        print(f"Day {d}: rebuilt with {len(programs)} program(s)")
