import json
import matplotlib.pyplot as plt

with open('result-2.json') as f:
    results = json.load(f)

n = [r["n"] for r in results]
skiplist = [r["skiplist"] for r in results]
bst = [r["bst"] for r in results]

plt.figure(figsize=(10, 6))
plt.plot(n, skiplist, marker='o', label='Skip List', color='blue')
plt.plot(n, bst, marker='s', label='Randomized BST', color='orange')

plt.xlabel('n (Элементийн тоо, Number of elements)')
plt.ylabel('Дундаж алхмын тоо (Avg step count)')
plt.title('Skip List vs Randomized BST - Дундаж алхмын харьцуулалт')
plt.grid(True, which='both', axis='both', linestyle='--', alpha=0.5)
plt.legend()
plt.show()