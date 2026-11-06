"""Capture a real Windows Terminal running a given exe, via keyboard-driven launch."""
import subprocess, time, os, sys
import pyautogui
import mss

base = os.path.dirname(os.path.abspath(__file__))
img  = os.path.join(base, "_img")

def find_term_window():
    """Find the Windows Terminal window rect using win32 via pywinauto."""
    from pywinauto import Desktop
    for w in Desktop(backend="uia").windows():
        try:
            cls = w.element_info.class_name()
            if "Terminal" in cls or "TerminalAppWindow" in cls or w.window_text() == "Windows Terminal":
                return w.rectangle()
        except Exception:
            pass
    return None

def capture(exe, inputs, key, setup=None):
    os.chdir(base)
    if setup=="read":   open("CSE21.txt","w").write("42 7 -3 15 0 -8 99\n")
    if setup=="posneg": open("Shagor.txt","w").write("10 -5 3 -1 7 -2 0 4\n")

    # Feed stdin via a temp redirect so the real terminal shows the running program.
    # We'll run: exe  <  stdinfile   inside the terminal so prompts+output all render.
    stdinf = os.path.join(img, "_stdin.txt")
    with open(stdinf,"w") as f:
        f.write("\n".join(inputs)+"\n")

    # Launch Windows Terminal (a new tab/window). Use wt with a command.
    cmd = f'"{exe}" < "{stdinf}"'
    subprocess.Popen("wt -d \"" + base + "\" " + cmd)
    time.sleep(4.0)  # let it compile? no—exe already built. Let program run + render.

    rect = find_term_window()
    if rect is None:
        print("  !! could not find terminal window")
        return None
    # Grow region a bit to capture full window incl. title bar
    with mss.mss() as sct:
        mon = {"left":rect.left, "top":rect.top, "width":rect.width, "height":rect.height}
        imgdata = sct.grab(mon)
        out = os.path.join(img, key+".png")
        pyautogui.screenshot()  # noop keep
        import mss.tools
        mss.tools.to_png(imgdata.rgb, imgdata.size, output=out)
    print(f"  captured {key}.png  {rect.width}x{rect.height}")
    return out

if __name__ == "__main__":
    import sys
    # test: build Day 4 (no input) and capture
    exe = os.path.join(img, "t4.exe")
    src = os.path.join(base, "Day 4", "In Lab", "code.cpp")
    subprocess.run(["g++","-o",exe,src], check=True, cwd=base)
    capture(exe, [], "test4")
    os.remove(exe)
    os.remove(os.path.join(img,"_stdin.txt"))
