from collections import namedtuple
from typing import List

Item = namedtuple("Item", "weight value")

def knapsack(max_weight: int, items: List[Item]):
    num_items = len(items)
    mat = [[0] * num_items for _ in range(num_items)]
    
    # Max weight at row i, column j max value with items 1,2,3,...i or 1,2,3,...i-1
    
    def get_item_weight(item):
        return item.weight
    
    def get_item_value(item):
        return item.value

    def helper(remaining_ind: List[int]):
        if len(remaining_ind) == 0:
            # If there's no more items, value = 0
            return 0
        elif len(remaining_ind) == 1:
            # If there's only 1 item, we include it or we don't
            if items[remaining_ind[0]].weight <= max_weight:
                return items[remaining_ind[0]].value
            else:
                return 0
        else:
            # We have 2 or more items
            # Next item is 

            # If we include it:
            if sum(map(get_item_weight, [items[i] for i in remaining_ind])) <= max_weight:
                return get_item_value(items[remaining_ind[0]]) + helper(remaining_ind[1:])

            # If we don't include it:
            elif sum(map(get_item_weight, [items[i] for i in remaining_ind[1:]])) <= max_weight:
                return helper(remaining_ind[1:])
            else:
                return 0
    
    max_values = []
    for i in range(num_items):
        # Pretend we exclude i
        max_values.append(helper([j for j in range(num_items)]))
        max_values.append(helper([j for j in range(num_items) if j != i]))
    print(max_values)
    return max(max_values)

if __name__ == "__main__":
    
    
    max_knapsack_weight = 10
    num_items = 4
    
    items = [
            Item(5, 10),
            Item(4, 40),
            Item(6, 30),
            Item(3, 50)
            ]

    result = knapsack(max_knapsack_weight, items)
    print(result)
