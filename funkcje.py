import pygame

def show_step(myfont, step, clad, length, screen, bg_color, text_color):
	mcs = "Monte Carlo Step: " + str(step)
	footer = myfont.render(mcs, False, text_color, bg_color)
	footer_rect = footer.get_rect()
	footer_rect.left = clad
	footer_rect.top = clad+length+10
	screen.blit(footer, footer_rect)
	
def show_L(myfont, L, clad, length, screen, bg_color, text_color):
	str_L = "L = " + str(L)
	image_L = myfont.render(str_L, False, text_color, bg_color)
	image_L_rect = image_L.get_rect()
	image_L_rect.left = clad
	image_L_rect.top = clad - 45
	screen.blit(image_L, image_L_rect)

def show_T(myfont, T, clad, screen, bg_color, text_color):
	str_T = "T = " + T
	image_T = myfont.render(str_T, False, text_color, bg_color)
	image_T_rect = image_T.get_rect()
	image_T_rect.left = 2*clad + 80
	image_T_rect.top = clad - 45
	screen.blit(image_T, image_T_rect)

def draw_array(arr, L, clad, size, light, dark, screen):
	for i in range(L):
		for j in range(L):
			left = clad + (size*j)
			top = clad + (size*i)
			position = (left, top, size, size)
			if arr[i][j] > 0:
				color = light
			else:
				color = dark
			pygame.draw.rect(screen, color, position)

def create_starting_screen(myfont, step, L, T, clad, length, screen, bg_color, text_color):
	show_step(myfont, step, clad, length, screen, bg_color, text_color)
	show_L(myfont, L, clad, length, screen, bg_color, text_color)
	show_T(myfont, T, clad, screen, bg_color, text_color)

def click_to_start():
	while True:
		for event in pygame.event.get():
			if event.type==pygame.KEYDOWN:
				if event.key==pygame.K_RETURN:
					return
