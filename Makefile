all:
	cd II/II/ && g++ -O3 *.cpp -o mhpsii && ./mhpsii

clean:
	cd II/II/ && rm mhpsii


