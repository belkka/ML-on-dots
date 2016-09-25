# -*- coding: utf-8 -*-


def parse():
    inp = open("input.txt", "w")
    ans = open("answers.txt", "w")

    with open("pendigits.tra", "r") as dataset:
        for line in dataset:
            arr = line.split(",")
            data, mark = arr[:-1], arr[-1]

            inp.write(" ".join(data) + "\n")
            ans.write(mark)

    inp.close()
    ans.close()


parse()
