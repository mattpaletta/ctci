from collections import namedtuple
from typing import List
import numpy as np
from datetime import datetime

Item = namedtuple("Item", "weight value")


def get_item_weight(item):
    return item.weight


def get_item_value(item):
    return item.value


def knapsack(max_weight: int, items: List[Item]):
    def helper(remaining_items: List[Item], remaining_weight: int, current_value: int):
        if len(remaining_items) == 0 or remaining_weight == 0:
            # If there's no more items, value = 0
            return 0
        elif len(remaining_items) == 1:
            # If there's only 1 item, we include it or we don't
            if get_item_weight(remaining_items[0]) <= remaining_weight:
                return get_item_value(remaining_items[0])
            else:
                return 0
        else:
            # We have 2 or more items
            return max(
                # Include the current item
                get_item_value(remaining_items[0]) + helper(remaining_items = remaining_items[1:],
                                                            remaining_weight= remaining_weight - get_item_weight(remaining_items[0]),
                                                            current_value= current_value + get_item_value(remaining_items[0])),
                # Don't include the current item
                helper(remaining_items= remaining_items[1:],
                       remaining_weight= remaining_weight,
                       current_value= current_value)
            )

    return helper(remaining_items=items,
                  remaining_weight=max_weight,
                  current_value=0)


def knapsack_memoize(max_weight: int, items: List[Item]):
    num_items = len(items)
    mat = np.zeros(shape=(num_items + 1, max_weight + 1))

    # Max weight at row i, column j max value with items 1,2,3,...i or 1,2,3,...i-1
    def get_item_weight(item):
        return item.weight

    def get_item_value(item):
        return item.value

    def helper_calculate(remaining_items: List[Item], remaining_weight: int, current_value: int):
        if len(remaining_items) == 0 or remaining_weight == 0:
            # If there's no more items, value = 0
            return 0
        elif len(remaining_items) == 1:
            # If there's only 1 item, we include it or we don't
            if get_item_weight(remaining_items[0]) <= remaining_weight:
                return get_item_value(remaining_items[0])
            else:
                return 0
        else:
            # We have 2 or more items
            return max(
                # Include the current item
                get_item_value(remaining_items[0]) + helper(remaining_items = remaining_items[1:],
                                                            remaining_weight= remaining_weight - get_item_weight(remaining_items[0]),
                                                            current_value= current_value + get_item_value(remaining_items[0])),
                # Don't include the current item
                helper(remaining_items= remaining_items[1:],
                       remaining_weight= remaining_weight,
                       current_value= current_value)
            )

    def helper(remaining_items: List[Item], remaining_weight: int, current_value: int):
        if len(remaining_items) == 0 or remaining_weight <= 0:
            return 0
        else:
            # find the last one that is not 0
            for i in range(remaining_weight, 0):
                if mat[len(remaining_items) - 1][i] >= 0:
                    return mat[len(remaining_items) - 1][i]

            result = helper_calculate(remaining_items, remaining_weight, current_value)
            mat[len(remaining_items) - 1][remaining_weight] = result
            return result

    return helper(remaining_items=items,
                  remaining_weight=max_weight,
                  current_value=0)


if __name__ == "__main__":
    max_knapsack_weight = 50

    items = [
        Item(10, 60),
        Item(20, 100),
        Item(30, 120),
            ]

    print("Working for {0} items ".format(len(items)))
    start = datetime.now()
    result = knapsack(max_knapsack_weight, items)
    print(datetime.now() - start)
    print(result)

    start = datetime.now()
    result = knapsack_memoize(max_knapsack_weight, items)
    print(datetime.now() - start)
    print(result)
