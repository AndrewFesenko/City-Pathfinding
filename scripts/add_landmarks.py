import csv
from geopy.geocoders import Nominatim
from geopy.distance import geodesic

nodes = []
with open("data/node_locations.csv", "r") as f:
	reader = csv.DictReader(f)
	for row in reader:
		nodes.append({
			"node_id": row["node_id"],
			"lat": float(row["lat"]),
			"lon": float(row["lon"])
		})

geolocator = Nominatim(user_agent="city-pathfinder")

with open("data/landmarks.csv", "w", newline="") as f_out:
	writer = csv.writer(f_out)
	writer.writerow(["name", "node_id", "lat", "lon"])

	while True:
		place = input("Enter landmark name")
		if place.lower() == "done":
			break

		location = geolocator.geocode(place)
		if not location:
			print("cant find location")
			continue

		place_coords = (location.latitude, location.longitude)

		closest = min(nodes, key=lambda n: geodesic((n["lat"], n["lon"]), place_coords).meters)
		distance = geodesic((closest["lat"], closest["lon"]), place_coords).meters

		print(f"the closest node to {place} is {closest['node_id']} ({distance:.1f} meters away)")
		writer.writerow([place, closest["node_id"], closest["lat"], closest["lon"]])
