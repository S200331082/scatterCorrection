import uproot
import pandas as pd

# 替换为你的 ROOT 文件路径
file_path = "../build/scatter_data.root"
tree_name = "Data"  # 修改为实际 TTree 名称（比如 Events、Tree、Data 等）

# 打开文件和 TTree
file = uproot.open(file_path)
tree = file[tree_name]

# 指定要读取的分支
branches = ["x", "y", "Ip", "Is", "Np", "Ns"]

# 读取为 pandas DataFrame
df = tree.arrays(branches, library="pd")

# 保存为 CSV
df.to_csv("output.csv", index=False)

print("✅ 数据已导出为 output.csv")
