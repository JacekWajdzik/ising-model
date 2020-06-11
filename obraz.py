import pygame

def picture():
	arrL = ["10", "50", "100"]
	arrT = ["1.00", "2.26", "4.00"]
	arrS = ["1", "250000", "500000", "750000", "1000000"]
	bg_color = (255, 255, 255)

	#inicjalizacja pyGame i utworzenie okna obrazu
	pygame.init()
	screen = pygame.display.set_mode((3000, 600))
	pygame.display.set_caption("Model Isinga")
	screen.fill(bg_color)
	for strL in arrL:
		for strT in arrT:
			n = 0
			for strS in arrS:
				fname = "single_images/image_L" + strL + "_T" + strT + "_step" + strS + ".png"
				image = pygame.image.load(fname)
				image_rect = image.get_rect()
				image_rect.left = n*600
				image_rect.top = 0
				screen.blit(image, image_rect)
				pygame.display.flip()
				n += 1
			image_name = "image_L" + strL + "_T" + strT + ".png"
			pygame.image.save(screen, image_name)


picture()
	



	

