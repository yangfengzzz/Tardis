import enum
from typing import overload


def MakeMatrixVariable(rows: int, cols: int, name: str, type: Variable.Type = Variable.Type.CONTINUOUS) -> "Eigen::Matrix<tardis::Variable, -1, -1, 0, -1, -1>": ...

class Variable:
    @overload
    def __init__(self) -> None: ...

    @overload
    def __init__(self, name: str, type: Variable.Type = Variable.Type.CONTINUOUS) -> None: ...

    class Type(enum.Enum):
        CONTINUOUS = 0

        INTEGER = 1

        BINARY = 2

        BOOLEAN = 3

        RANDOM_UNIFORM = 4

        RANDOM_GAUSSIAN = 5

        RANDOM_EXPONENTIAL = 6

    def is_dummy(self) -> bool: ...

    def get_id(self) -> int: ...

    def get_type(self) -> Variable.Type: ...

    def get_name(self) -> str: ...

    def equal_to(self, arg: Variable, /) -> bool: ...

    def less(self, arg: Variable, /) -> bool: ...

    def __str__(self) -> str: ...

    def __repr__(self) -> str: ...
