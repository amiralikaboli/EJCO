from enum import Enum

class Optimisation(Enum):
    HASHMAP = 0
    VECTOR = 1
    SMALL_VECTOR = 2
    DEAD_CODE_ELIMINATION = 2.5
    ELIMINATING_REDUNDANT_OFFSETS = 3
    EARLY_AGGREGATION = 3.5
    LOOP_INVARIANT_CODE_MOTION = 4


MAX_OPTIMISATION = max(Optimisation, key=lambda x: x.value)


def to_hint(optimisation: Optimisation) -> str:
    if optimisation.value >= Optimisation.SMALL_VECTOR.value:
        return "@smallvecdict(4)"
    elif optimisation == Optimisation.VECTOR:
        return "@smallvecdict(0)"
    else:
        return ""
