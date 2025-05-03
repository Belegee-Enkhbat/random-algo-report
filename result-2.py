import matplotlib.pyplot as plt

# Өгөгдлүүд
n_values = [5_000_000, 10_000_000, 20_000_000, 50_000_000]
skip_list_steps = [100.97, 190.45, 315.82, 792.10]
rand_bst_steps = [28.95, 32.63, 31.65, 33.55]

# График зурна
plt.figure(figsize=(10, 6))
plt.plot(n_values, skip_list_steps, marker='o', label='Skip List')
plt.plot(n_values, rand_bst_steps, marker='s', label='Randomized BST')
plt.title('Skip List vs Randomized BST - Дундаж алхмын харьцуулалт')
plt.xlabel('n (Элементийн тоо)')
plt.ylabel('Дундаж алхмын тоо')
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.show()
