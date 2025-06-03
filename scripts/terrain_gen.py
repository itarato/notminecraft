class TerrainGen:
    def __init__(self, w: int, h: int) -> None:
        self.w = w
        self.h = h

    def generate(self) -> list[list[int]]:
        matrix = []
        for _ in range(self.h):
            matrix.append([0] * self.w)

        return matrix


def export(matrix: list[list[int]], file_path: str):
    with open(file_path, "w") as f:
        f.write(str(len(matrix[0])) + " " + str(len(matrix)) + "\n")

        for row in matrix:
            for i, height in enumerate(row):
                f.write(str(height))
                if i < len(row) - 1:
                    f.write(" ")

            f.write("\n")


if __name__ == "__main__":
    tg = TerrainGen(100, 100)
    export(tg.generate(), "./test.map")
