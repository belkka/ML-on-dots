# coding: utf-8
import numpy as np


class params:
    K = 10  # количество кластеров
    alg = "k-medians"  # ...
    init = "randpart"  # метод инициализации
    dtype = int  # тип координат вектора (для цифр int для ирисов float)


class io:
    @staticmethod
    def read_input(dtype=float):
        with open("input.txt") as raw_data:
            return np.loadtxt(raw_data, dtype=dtype)

    @staticmethod
    def write_output(clusters):
        with open("output.txt", "w") as out:
            for c in clusters:
                out.write(" ".join(map(str, c)) + "\n")


def np_hash(vec):
    return hash(vec.tostring())


class KMeans:
    def __init__(self, K, init, distance, cent):
        self.K = K
        self.init = init
        self.distance = distance
        self.cent = cent

    def assignment_step(self, X):
        # этап распределения всех векторов в кластеры с ближайшими центрами
        self.clusters = [list() for __ in xrange(self.K)]  # опустошение

        for (i, x) in enumerate(X):
            self.clusters[np.argmin(
                [self.distance(x, c) for c in self.centers]
            )].append(i)

    def update_step(self, X):
        # этап перерасчёта центров
        self.centers = np.array([
            self.cent(np.take(X, c, axis=0), axis=0) for c in self.clusters
        ])

    def fit_predict(self, X):
        self.clusters, self.centers = self.init(X, self.K)

        if self.centers is None:
            self.update_step(X)

        hash_prev, hash_curr = 0, 1

        while hash_prev != hash_curr:
            self.assignment_step(X)
            self.update_step(X)

            hash_prev = hash_curr
            hash_curr = np_hash(self.centers)

        return self.clusters


class init:
    # Функции инициализации возвращают пару
    #  (начальные кластеры, начальные центры)
    # В зависимости от метода одно из двух принимает значение None
    @staticmethod
    def forgy(X, K):
        indices = np.random.choice(len(X), K, replace=False)
        return (None, np.take(X, indices, axis=0))

    @staticmethod
    def randpart(X, K):
        # сдучайно делит всю выборку на K приблизительно равных кластеров
        sz = len(X)
        d, m = divmod(sz, K)
        edges = np.concatenate((
            np.arange(d + 1, m * (d + 1) + 1, d + 1),
            np.arange(m * (d + 1) + d, sz, d)
        ))
        return (np.split(np.random.permutation(sz), edges), None)


class dist:
    @staticmethod
    def euclid(x, y):  # квадрат евклидова расстояния
        return ((x - y) ** 2).sum()

    @staticmethod
    def manhattan(x, y):
        return abs(x - y).sum()


algorithmes = {
    "k-means": (dist.euclid, np.mean),
    "k-medians": (dist.manhattan, np.median)
}

init_methods = {
    "forgy": init.forgy,
    "randpart": init.randpart,
}


def main():
    distance, center = algorithmes[params.alg]

    brain = KMeans(params.K, init_methods[params.init], distance, center)

    io.write_output(brain.fit_predict(io.read_input(params.dtype)))


if __name__ == "__main__":
    main()
