from numpy import arange
from random import uniform


class Gen_formul():

    alph: list = []
    alph_svg: dict = {}

    dx: float = 0
    dy: float = 0

    rdx: float = 0
    rdy: float = 0

    symbolWidth: float = 30

    def __init__(self):
        alph: list = []
        alph_svg: dict = {}

        with open('./alph.txt') as f1:
            for line in f1.read().splitlines():
                if ":" in line:
                    tmp = line.split(":")
                    d = tmp[1].split(",")
                    alph_svg[tmp[0]] = {'svg': tmp[2],
                                        'dx': float(d[0]), 'dy': float(d[1])}
                    alph.append(tmp[0])
            f1.close()

        self.alph_svg = alph_svg
        self.alph = alph

    def set_dpos(self, dx: float = 0, dy: float = 0) -> None:
        self.dx = dx
        self.dy = dy

    def set_rpos(self, rdx: float = 0, rdy: float = 0) -> None:
        self.rdx = rdx
        self.rdy = rdy

    def txt_to_form(self, text: str) -> list:
        form = []

        for i in range(len(text)):
            (a, b) = self.svg_to_arr(self.alph_svg[text[i]], i)
            form = form + a
        return form

    # return list formul and list numbers for graph
    def txt_to_fn(self, text: str) -> (list, list):
        form: list = []
        np: list = []

        for i in range(len(text)):
            (a, b) = self.svg_to_arr(self.alph_svg[text[i]], i, True)
            form += a
            np += b
        return form, np

    # return list formul and list numbers for graph
    def debug(self, text: str) -> (list, list):
        import matplotlib.pyplot as plt

        form: list = []
        np: list = []

        for i in range(len(text)):
            (a, b) = self.svg_to_arr(self.alph_svg[text[i]], i, True)
            form += a
            np += b

        with open("./debug/formul.txt", "w") as f2:
            for x in form:
                f2.write(f"f(t) = ({x[0]}; {x[1]}), x=>[0,1]\n")
            f2.close()

        with open("./debug/num.txt", "w") as f2:
            for x in np:
                plt.plot(x[0], x[1])
                for xx in range(len(x[0])):
                    tmp = f"{x[0][xx]}\t{x[1][xx]}\n"
                    tmp = tmp.replace(".", ",")
                    f2.write(tmp)
            f2.close()

        plt.show()

        return form, np

    def svg_to_arr(self, svg_obj: object, position: int, ret_plot: bool = False, delta: float = 0.01) -> (list, list):
        svg: str = svg_obj['svg']
        dx: float = position*self.symbolWidth + uniform(-1*self.rdx, self.rdx)+self.dx + svg_obj['dx']
        dy: float = self.dy + uniform(-1*self.rdy, self.rdy) + svg_obj['dy']

        svg_arr: list = svg.split(" ")
        svg_arr.append("!")  # End

        end_point: list = [0.0, 0.0]
        start_point: list = [0.0, 0.0]
        ret: list = []
        ret_num: list = []

        if len(svg_arr) >= 2:
            i: int = 0
            while i < len(svg_arr):

                if svg_arr[i] == "!":
                    # print(f"! {i}")
                    break
                elif svg_arr[i] == "M":
                    # print(f"M {i}")
                    i += 1
                    end_point = [float(x) for x in svg_arr[i].split(",")]
                    start_point = end_point

                    f = "," in svg_arr[i+1]
                    while f:
                        f = False
                        # print(f"ML {i}")
                        S = end_point
                        i += 1
                        E = [float(x) for x in svg_arr[i].split(",")]

                        x = f"(1-t)*{round(S[0]+dx, 4)} + t*{round(E[0]+dx, 4)}"
                        y = f"(1-t)*{round(S[1]+dy, 4)} + t*{round(E[1]+dy, 4)}"
                        ret.append([x, y])

                        if ret_plot:
                            xn = [(1-t)*(S[0]+dx) + t*(E[0]+dx)
                                  for t in arange(0, 1+delta, delta)]
                            yn = [(1-t)*(S[1]+dy) + t*(E[1]+dy)
                                  for t in arange(0, 1+delta, delta)]
                            ret_num.append([xn, yn])

                        end_point = E
                        if "," in svg_arr[i+1]:
                            f = True

                elif svg_arr[i] == "m":
                    # print(f"m {i}")
                    i += 1
                    S = end_point
                    E = [float(x) for x in svg_arr[i].split(",")]
                    end_point = [S[0]+E[0], S[1]+E[1]]
                    start_point = end_point

                    f = "," in svg_arr[i+1]
                    while f:
                        f = False
                        # print(f"ml {i}")
                        S = end_point
                        i += 1
                        E = [float(x) for x in svg_arr[i].split(",")]
                        E = [S[0]+E[0], S[1]+E[1]]

                        x = f"(1-t)*{round(S[0]+dx, 4)} + t*{round(E[0]+dx, 4)}"
                        y = f"(1-t)*{round(S[1]+dy, 4)} + t*{round(E[1]+dy, 4)}"
                        ret.append([x, y])

                        if ret_plot:
                            xn = [(1-t)*(S[0]+dx) + t*(E[0]+dx)
                                  for t in arange(0, 1+delta, delta)]
                            yn = [(1-t)*(S[1]+dy) + t*(E[1]+dy)
                                  for t in arange(0, 1+delta, delta)]
                            ret_num.append([xn, yn])

                        end_point = E
                        if "," in svg_arr[i+1]:
                            f = True

                elif svg_arr[i] == "C":
                    f = True
                    while f:
                        f = False
                        # print(f"C {i}")
                        S = end_point
                        i += 1
                        A = [float(x) for x in svg_arr[i].split(",")]
                        i += 1
                        B = [float(x) for x in svg_arr[i].split(",")]
                        i += 1
                        E = [float(x) for x in svg_arr[i].split(",")]

                        x = f"((1-t)^3)*{round(S[0]+dx, 4)} + 3*((1-t)^2)*t*{round(A[0]+dx, 4)} + 3*(1-t)*(t^2)*{round(B[0]+dx, 4)} + (t^3)*{round(E[0]+dx, 4)}"
                        y = f"((1-t)^3)*{round(S[1]+dy, 4)} + 3*((1-t)^2)*t*{round(A[1]+dy, 4)} + 3*(1-t)*(t^2)*{round(B[1]+dy, 4)} + (t^3)*{round(E[1]+dy, 4)}"
                        ret.append([x, y])

                        if ret_plot:
                            xn = [((1-t)**3)*(S[0]+dx) + 3*((1-t)**2)*t*(A[0]+dx) + 3*(1-t)*(t**2)*(
                                B[0]+dx) + (t**3)*(E[0]+dx) for t in arange(0, 1+delta, delta)]
                            yn = [((1-t)**3)*(S[1]+dy) + 3*((1-t)**2)*t*(A[1]+dy) + 3*(1-t)*(t**2)*(
                                B[1]+dy) + (t**3)*(E[1]+dy) for t in arange(0, 1+delta, delta)]
                            ret_num.append([xn, yn])

                        end_point = E
                        if "," in svg_arr[i+1]:
                            f = True

                elif svg_arr[i] == "c":
                    f = True
                    while f:
                        f = False
                        # print(f"c {i}")
                        S = end_point
                        i += 1
                        A = [float(x) for x in svg_arr[i].split(",")]
                        A = [S[0]+A[0], S[1]+A[1]]
                        i += 1
                        B = [float(x) for x in svg_arr[i].split(",")]
                        B = [S[0]+B[0], S[1]+B[1]]
                        i += 1
                        E = [float(x) for x in svg_arr[i].split(",")]
                        E = [S[0]+E[0], S[1]+E[1]]

                        x = f"((1-t)^3)*{round(S[0]+dx, 4)} + 3*((1-t)^2)*t*{round(A[0]+dx, 4)} + 3*(1-t)*(t^2)*{round(B[0]+dx, 4)} + (t^3)*{round(E[0]+dx, 4)}"
                        y = f"((1-t)^3)*{round(S[1]+dy, 4)} + 3*((1-t)^2)*t*{round(A[1]+dy, 4)} + 3*(1-t)*(t^2)*{round(B[1]+dy, 4)} + (t^3)*{round(E[1]+dy, 4)}"
                        ret.append([x, y])

                        if ret_plot:
                            xn = [((1-t)**3)*(S[0]+dx) + 3*((1-t)**2)*t*(A[0]+dx) + 3*(1-t)*(t**2)*(
                                B[0]+dx) + (t**3)*(E[0]+dx) for t in arange(0, 1+delta, delta)]
                            yn = [((1-t)**3)*(S[1]+dy) + 3*((1-t)**2)*t*(A[1]+dy) + 3*(1-t)*(t**2)*(
                                B[1]+dy) + (t**3)*(E[1]+dy) for t in arange(0, 1+delta, delta)]
                            ret_num.append([xn, yn])

                        end_point = E
                        if "," in svg_arr[i+1]:
                            f = True
                elif svg_arr[i] == "Q":
                    f = True
                    while f:
                        f = False
                        # print(f"Q {i}")
                        S = end_point
                        i += 1
                        A = [float(x) for x in svg_arr[i].split(",")]
                        i += 1
                        E = [float(x) for x in svg_arr[i].split(",")]

                        x = f"((1-t)^2)*{round(S[0]+dx, 4)} + 2*(1-t)*t*{round(A[0]+dx, 4)} + (t^2)*{round(E[0]+dx, 4)}"
                        y = f"((1-t)^2)*{round(S[1]+dy, 4)} + 2*(1-t)*t*{round(A[1]+dy, 4)} + (t^2)*{round(E[1]+dy, 4)}"
                        ret.append([x, y])

                        if ret_plot:
                            xn = [((1-t)**2)*(S[0]+dx) + 2*(1-t)*t*(A[0]+dx) +
                                  (t**2)*(E[0]+dx) for t in arange(0, 1+delta, delta)]
                            yn = [((1-t)**2)*(S[1]+dy) + 2*(1-t)*t*(A[1]+dy) +
                                  (t**2)*(E[1]+dy) for t in arange(0, 1+delta, delta)]
                            ret_num.append([xn, yn])

                        end_point = E
                        if "," in svg_arr[i+1]:
                            f = True

                elif svg_arr[i] == "q":
                    f = True
                    while f:
                        f = False
                        # print(f"q {i}")
                        S = end_point
                        i += 1
                        A = [float(x) for x in svg_arr[i].split(",")]
                        A = [S[0]+A[0], S[1]+A[1]]
                        i += 1
                        E = [float(x) for x in svg_arr[i].split(",")]
                        E = [S[0]+E[0], S[1]+E[1]]

                        x = f"((1-t)^2)*{round(S[0]+dx, 4)} + 2*(1-t)*t*{round(A[0]+dx, 4)} + (t^2)*{round(E[0]+dx, 4)}"
                        y = f"((1-t)^2)*{round(S[1]+dy, 4)} + 2*(1-t)*t*{round(A[1]+dy, 4)} + (t^2)*{round(E[1]+dy, 4)}"
                        ret.append([x, y])

                        if ret_plot:
                            xn = [((1-t)**2)*(S[0]+dx) + 2*(1-t)*t*(A[0]+dx) +
                                  (t**2)*(E[0]+dx) for t in arange(0, 1+delta, delta)]
                            yn = [((1-t)**2)*(S[1]+dy) + 2*(1-t)*t*(A[1]+dy) +
                                  (t**2)*(E[1]+dy) for t in arange(0, 1+delta, delta)]
                            ret_num.append([xn, yn])

                        end_point = E
                        if "," in svg_arr[i+1]:
                            f = True
                elif svg_arr[i] == "H":
                    # print(f"H {i}")
                    S = end_point
                    i += 1
                    E = [float(svg_arr[i]), S[1]]

                    x = f"(1-t)*{round(S[0]+dx, 4)} + t*{round(E[0]+dx, 4)}"
                    y = "{"+f"{round(S[1]+dy, 4)}"+"}"
                    ret.append([x, y])

                    if ret_plot:
                        xn = [(1-t)*(S[0]+dx) + t*(E[0]+dx)
                              for t in arange(0, 1+delta, delta)]
                        yn = [S[1]+dy for t in arange(0, 1+delta, delta)]
                        ret_num.append([xn, yn])

                    end_point = E

                elif svg_arr[i] == "h":
                    # print(f"h {i}")
                    S = end_point
                    i += 1
                    E = [float(svg_arr[i]), S[1]]
                    E = [S[0]+E[0], S[1]]

                    x = f"(1-t)*{round(S[0]+dx, 4)} + t*{round(E[0]+dx, 4)}"
                    y = "{"+f"{round(S[1]+dy, 4)}"+"}"
                    ret.append([x, y])

                    if ret_plot:
                        xn = [(1-t)*(S[0]+dx) + t*(E[0]+dx)
                              for t in arange(0, 1+delta, delta)]
                        yn = [S[1]+dy for t in arange(0, 1+delta, delta)]
                        ret_num.append([xn, yn])

                    end_point = E

                elif svg_arr[i] == "V":
                    # print(f"V {i}")
                    S = end_point
                    i += 1
                    E = [S[0], float(svg_arr[i])]

                    x = "{"+f"{round(S[0]+dx, 4)}"+"}"
                    y = f"(1-t)*{round(S[1]+dy, 4)} + t*{round(E[1]+dy, 4)}"
                    ret.append([x, y])

                    if ret_plot:
                        xn = [(S[0]+dx) for t in arange(0, 1+delta, delta)]
                        yn = [(1-t)*(S[1]+dy) + t*(E[1]+dy)
                              for t in arange(0, 1+delta, delta)]
                        ret_num.append([xn, yn])

                    end_point = E

                elif svg_arr[i] == "v":
                    # print(f"v {i}")
                    S = end_point
                    i += 1
                    E = [S[0], float(svg_arr[i])]
                    E = [S[0], S[1]+E[1]]

                    x = "{"+f"{round(S[0]+dx, 4)}"+"}"
                    y = f"(1-t)*{round(S[1]+dy, 4)} + t*{round(E[1]+dy, 4)}"
                    ret.append([x, y])

                    if ret_plot:
                        xn = [(S[0]+dx) for t in arange(0, 1+delta, delta)]
                        yn = [(1-t)*(S[1]+dy) + t*(E[1]+dy)
                              for t in arange(0, 1+delta, delta)]
                        ret_num.append([xn, yn])

                    end_point = E

                elif svg_arr[i] == "L":
                    # print(f"L {i}")
                    f = True
                    while f:
                        f = False
                        S = end_point
                        i += 1
                        E = [float(x) for x in svg_arr[i].split(",")]

                        x = f"(1-t)*{round(S[0]+dx, 4)} + t*{round(E[0]+dx, 4)}"
                        y = f"(1-t)*{round(S[1]+dy, 4)} + t*{round(E[1]+dy, 4)}"
                        ret.append([x, y])

                        if ret_plot:
                            xn = [(1-t)*(S[0]+dx) + t*(E[0]+dx)
                                  for t in arange(0, 1+delta, delta)]
                            yn = [(1-t)*(S[1]+dy) + t*(E[1]+dy)
                                  for t in arange(0, 1+delta, delta)]
                            ret_num.append([xn, yn])

                        end_point = E
                        if "," in svg_arr[i+1]:
                            f = True

                elif svg_arr[i] == "l":
                    # print(f"l {i}")
                    f = True
                    while f:
                        f = False
                        S = end_point
                        i += 1
                        E = [float(x) for x in svg_arr[i].split(",")]
                        E = [S[0]+E[0], S[1]+E[1]]

                        x = f"(1-t)*{round(S[0]+dx, 4)} + t*{round(E[0]+dx, 4)}"
                        y = f"(1-t)*{round(S[1]+dy, 4)} + t*{round(E[1]+dy, 4)}"
                        ret.append([x, y])

                        if ret_plot:
                            xn = [(1-t)*(S[0]+dx) + t*(E[0]+dx)
                                  for t in arange(0, 1+delta, delta)]
                            yn = [(1-t)*(S[1]+dy) + t*(E[1]+dy)
                                  for t in arange(0, 1+delta, delta)]
                            ret_num.append([xn, yn])

                        end_point = E
                        if "," in svg_arr[i+1]:
                            f = True

                elif svg_arr[i] == "z" or svg_arr[i] == "Z":
                    # print(f"z {i}")
                    S = end_point
                    E = start_point

                    x = f"(1-t)*{round(S[0]+dx, 4)} + t*{round(E[0]+dx, 4)}"
                    y = f"(1-t)*{round(S[1]+dy, 4)} + t*{round(E[1]+dy, 4)}"
                    ret.append([x, y])

                    if ret_plot:
                        xn = [(1-t)*(S[0]+dx) + t*(E[0]+dx)
                              for t in arange(0, 1+delta, delta)]
                        yn = [(1-t)*(S[1]+dy) + t*(E[1]+dy)
                              for t in arange(0, 1+delta, delta)]
                        ret_num.append([xn, yn])

                    end_point = E

                else:
                    print("[Error] "+svg_arr[i])
                i += 1
        return ret, ret_num
