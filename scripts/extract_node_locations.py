import csv

input_path = "data/city_edges.csv"
output_path = "data/node_locations.csv"

seen = set()
with open(input_path, "r") as f_in, open(output_path, "w", newline="") as f_out:
	reader = csv.DictReader(f_in)
	writer = csv.writer(f_out)
	writer.writerow(["node_id", "lat", "lon"])

	for row in reader:
		for node, lon, lat in [(row["from"], row["x1"], row["y1"]), (row["to"], row["x2"], row["y2"])]:
			if node not in seen:
				seen.add(node)
				writer.writerow([node, lat, lon])
