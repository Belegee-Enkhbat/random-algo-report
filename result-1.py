import json
import matplotlib.pyplot as plt
import numpy as np
import matplotlib.ticker as mtick

with open('result-1.json', 'r') as f:
    data = json.load(f)

ns = [d['n'] for d in data]
qs_time = [d['quickselect'] * 1000 for d in data]  
sort_time = [d['quicksort'] * 1000 for d in data] 

plt.figure(figsize=(10, 6))
plt.plot(ns, sort_time, marker='o', markersize=6, color='#5296d8', label='Quicksort')
plt.plot(ns, qs_time, marker='s', markersize=6, color='#ffa154', label='Quickselect')

poly_sort = np.polyfit(ns, sort_time, 1)
poly_qs = np.polyfit(ns, qs_time, 1)
plt.plot(ns, np.polyval(poly_sort, ns), color='#5296d8', linestyle=':', label='Linear (Quicksort)')
plt.plot(ns, np.polyval(poly_qs, ns), color='#ffa154', linestyle=':', label='Linear (Quickselect)')

plt.xlabel('Input Size (N)')
plt.ylabel('Time (ms)')
plt.title('Quickselect vs Quicksort Performance')

plt.gca().xaxis.set_major_formatter(mtick.FuncFormatter(lambda x, _: f'{int(x):,}'))

plt.grid(True, which='both', axis='both', linestyle='--', alpha=0.5)
plt.legend()

plt.tight_layout()
plt.savefig('quick_vs_sort_benchmark.png', dpi=300)
plt.show()
