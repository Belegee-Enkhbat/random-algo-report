import matplotlib.pyplot as plt

# Мэдээлэл
input_sizes = [1_000_000, 2_000_000, 4_000_000, 8_000_000, 16_000_000]
quickselect_times = [0.013757, 0.027673, 0.054179, 0.105701, 0.211265]
sort_times = [0.101036, 0.209249, 0.417751, 0.818184, 1.590076]

# График үүсгэх
plt.figure(figsize=(10, 6))
plt.plot(input_sizes, quickselect_times, marker='o', label='QuickSelect')
plt.plot(input_sizes, sort_times, marker='s', label='Эрэмдэлэлт (QuickSort)')

# Хэмжээний тэнхлэгүүд лог масштабтай болгох (заавал биш, гэхдээ ойлгомжтой болгодог)
plt.xscale('log')
plt.yscale('log')

# Утгуудыг цэг бүр дээр бичих
for x, y in zip(input_sizes, quickselect_times):
    plt.text(x, y, f"{y:.3f}", ha='right', va='bottom', fontsize=8)
for x, y in zip(input_sizes, sort_times):
    plt.text(x, y, f"{y:.3f}", ha='left', va='bottom', fontsize=8)

# Тайлбар, шошго, тор
plt.xlabel('Оролтын хэмжээ (n)')
plt.ylabel('Дундаж хугацаа (секундээр)')
plt.title('QuickSelect ба Эрэмдэлэлтийн харьцуулалт (лог масштаб)')
plt.legend()
plt.grid(True, which="both", linestyle='--', linewidth=0.5)
plt.tight_layout()

# PNG файл болгон хадгалах
plt.savefig("benchmark_comparison.png", dpi=300)

# График харуулах
plt.show()
