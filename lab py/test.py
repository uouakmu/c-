import sys
input = sys.stdin.readline

n=int(input())
coords = list(map(int, input().split()))

coords_dict = {value: index for index, value in enumerate(sorted(set(coords)))}
compressed_coords = [coords_dict[x] for x in coords]

print(' '.join(map(str, compressed_coords)))