import pygame
import sys
import funkcje as f
from time import sleep

def run_animation(L, T, fname):
	
	length = 500 #szerokość pola animacji [px]
	clad = 50 #odstęp pola od krawędzi okna [px]
	size = int(length/L) #szerokość i wysokość jednej cząstki [px]
	#kolory rgb
	white = (255, 255, 255)
	black = (0, 0, 0)
	light = (255, 214, 193)
	dark = (240, 78, 0)
	bg_color = white
	text_color = black
		
	#inicjalizacja pyGame i utworzenie okna animacji
	pygame.init()
	pygame.font.init()
	screen = pygame.display.set_mode((2*clad+length, 2*clad+length))
	pygame.display.set_caption("Model Isinga")
	screen.fill(bg_color)
	
	#wyświetlenie parametrów symulacji
	myfont = pygame.font.SysFont('Times New Roman', 30, True)
	f.create_starting_screen(myfont, 0, L, T, clad, length, screen, bg_color, text_color)
	#odświeżenie ekranu
	pygame.display.flip()
	f.click_to_start()
	arr = []
	row = []
	#otwarcie pliku
	with open(fname) as dane:
		lines = dane.readlines() #odczytanie zawartości pliku
		counter = 0 #licznik kroków
		for line in lines: #czytanie po linijce
			if (counter%(L+1)==0 and counter>0):
				f.draw_array(arr, L, clad, size, light, dark, screen)
				f.show_step(myfont, step, clad, length, screen, bg_color, text_color)
				pygame.display.flip()
				if (step==1 or (step%250000==0 and counter>0)):
					image_name = "image_L" + str(L) + "_T" + T + "_step" + str(step) + ".png"
					pygame.image.save(screen, image_name)
				#sleep(0.04) #regulacja tempa wyświetlanej animacji
			if(counter%(L+1)==0):
				step = int(line)
				arr = []
			else:
				row_str = line.split() #wczytanie współrzędnych do tablicy
				for spin in row_str:
					row.append(int(spin))
				arr.append(row)
				row_str = []
				row = []	
			counter += 1
			
			#reakcja na zamknięcie okna animacji
			for event in pygame.event.get():
				if event.type == pygame.QUIT:
					sys.exit()
	f.draw_array(arr, L, clad, size, light, dark, screen)
	f.show_step(myfont, step, clad, length, screen, bg_color, text_color)
	pygame.display.flip()
	image_name = "image_L" + str(L) + "_T" + T + "_step" + str(step) + ".png"
	pygame.image.save(screen, image_name)
	#Zamknięcie okna dowolnym klawiszem
	while True:
		for event in pygame.event.get():
			if event.type == pygame.QUIT:
				sys.exit()
			if event.type==pygame.KEYDOWN:
				return


arrL = [10, 50, 100]
arrT = ["1.00", "2.26", "4.00"]
for L in arrL:
	for T in arrT:
		fname = "spinch/spinch_L" + str(L) + "_T" + T + ".txt"
		run_animation(L, T, fname)


	
