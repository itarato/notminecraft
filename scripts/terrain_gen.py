import random
import math

MAX_RANDOM_BUMP = 2
BUMP_SPREAD = 5
BUMP_COUNT = 50
MAP_SIZE = 30


class TerrainGen:
    def __init__(self, w: int, h: int) -> None:
        self.w = w
        self.h = h

    def generate(self) -> list[list[int]]:
        matrix = []
        for _ in range(self.h):
            matrix.append([0] * self.w)

        for _ in range(BUMP_COUNT):
            apply_bump(
                matrix,
                random.randrange(0, MAP_SIZE),
                random.randrange(0, MAP_SIZE),
                MAX_RANDOM_BUMP,
                BUMP_SPREAD,
                MAP_SIZE,
            )

        return matrix


def apply_bump(
    matrix: list[list[int]],
    x: int,
    z: int,
    height: int,
    spread: int,
    coord_limit: int,
) -> None:
    for xoffs in range(-spread, spread + 1):
        for zoffs in range(-spread, spread + 1):
            xabs = x + xoffs
            zabs = z + zoffs

            if xabs < 0 or zabs < 0 or xabs >= coord_limit or zabs >= coord_limit:
                continue

            dist = math.sqrt((xoffs**2) + (zoffs**2))
            if dist >= spread:
                continue

            lift = math.sin((spread - dist) / (spread / math.pi * 2.0)) * height
            matrix[x + xoffs][z + zoffs] += lift


def export(matrix: list[list[int]], file_path: str):
    with open(file_path, "w") as f:
        f.write(str(MAP_SIZE) + "\n")

        for row in matrix:
            for i, height in enumerate(row):
                f.write(str(round(height)))
                if i < len(row) - 1:
                    f.write(" ")

            f.write("\n")


if __name__ == "__main__":
    tg = TerrainGen(MAP_SIZE, MAP_SIZE)
    export(tg.generate(), "./test.map")
