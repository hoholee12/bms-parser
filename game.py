#!/usr/bin/env python
import pygame
import pygame.gfxdraw
import math
import bmsreader
import time
pygame.init()

'''
4bytes 32bit hex: 0x0~0xffffffff(8) dec: 0~4294967295
2bytes 16bit hex: 0x0~0xffff(4) dec: 0~65535
1byte 8bit hex: 0x0~0xff(2) dec: 0~255
'''

black=(0x0, 0x0, 0x0)
white=(0xff, 0xff, 0xff)
red=(0xff, 0x0f, 0x0f)
green=(0x0f, 0xff, 0x0f)
blue=(0x0f, 0x0f, 0xff)
lightblue=(0x0, 0xbf, 0xff)
gray=(0x80, 0x80, 0x80)
orange=(0xff, 0xa5, 0x0)

pi=3.141592653


width=854
height=480
size=(width, height)
screen=pygame.display.set_mode(size)

pygame.display.set_caption("TENDON vibes v0.02")

done=False

clock=pygame.time.Clock() #for clock.tick(60)

fps=240

timetosleep=0
'''
game vars============================================================
'''

player_image=pygame.image.load("player.png").convert()
player_image.set_colorkey(white)


class note:
	def __init__(self, color, str, loc=[0, 0, 0, 0]):
		self.color=color
		self.str=str
		self.loc=loc

	def printnote(self):
		pygame.gfxdraw.box(screen, pygame.Rect(self.loc[0], self.loc[1], self.loc[2], self.loc[3]), self.color)
			

	def playmusic(self):
		if self.loc[1]>380:
			self.loc[1]=-100000000
			return True
		else:
			return False



class keys:
	#tweak bar length and speed here
	max=200.0
	speed=max/(fps/6.0)
	
	angle=360 #turntable
	val=[0,0,0,0,0,0,0,0] #zsxdcfv shift
	on=[0,0,0,0,0,0,0,0] #zsxdcfv shift
	lock=[0,0,0,0,0,0,0,0] #zsxdcfv shift

	def __init__(self, init):
		if init != 0:
			angle=360 #turntable
			self.val=[0,0,0,0,0,0,0,0] #zsxdcfv shift
			self.on=[0,0,0,0,0,0,0,0] #zsxdcfv shift
			self.lock=[0,0,0,0,0,0,0,0] #zsxdcfv shift

	def draw(self, screen, loc=[0,0]):
		max=240 #hax
		x=0
		for i in range(0, 7):
			if i%2 == 0:
				pygame.gfxdraw.box(screen, pygame.Rect(loc[0]+x, loc[1]-480, 30, 760), (0x0, 0xbf, 0x0, (self.val[i] + 1) / 2))
				x+=30
			else:
				pygame.gfxdraw.box(screen, pygame.Rect(loc[0]+x, loc[1]-480, 25, 760), (0x0, 0xbf, 0xff, (self.val[i] + 1)/ 2))
				x+=25
				
				
				
	def drawscratch(self, screen, loc=[0,0]):
		max=240 #hax
		pygame.gfxdraw.box(screen, pygame.Rect(loc[0]-50, loc[1]-480, 50, 760), (0xbf, 0xbf, 0x0, (self.val[7] + 1) / 2))
		pygame.draw.ellipse(screen, gray, [loc[0]-50, loc[1]+max, 50, 30])
		if self.on[7] == 1:
			pygame.draw.ellipse(screen, orange, [loc[0]-50+10, loc[1]+max+5, 30, 20])
			self.angle-=self.speed/(fps/480.0)
			self.angle%=360
		else:
			pygame.draw.ellipse(screen, lightblue, [loc[0]-50+10, loc[1]+max+5, 30, 20])
		newimg=pygame.transform.rotate(player_image, self.angle)
		newimg=pygame.transform.scale(newimg, [30, 20])
		
		screen.blit(newimg, [loc[0]-50+10, loc[1]+max+5])

		
	def drawline(self, screen, loc=[0,0]):
		pygame.draw.rect(screen, white, [loc[0], loc[1], 195, 1]) #bpm vertical bar


				
	def drawunder(self, screen, font, loc=[0,0]):
		loc[1]+=200 #hax
		x=0
		for i in range(0, 7):
			if i%2 ==0:
				if self.on[i] == 1:
					pygame.draw.rect(screen, orange, [loc[0]+x, loc[1]+50, 30, 50])
					text=font.render(str(self.on[i]), True, white)
					screen.blit(text, [loc[0]+x, loc[1]+50])
					x+=30
				else:
					pygame.draw.rect(screen, gray, [loc[0]+x, loc[1]+50, 30, 50])
					text=font.render(str(self.on[i]), True, black)
					screen.blit(text, [loc[0]+x, loc[1]+50])
					x+=30
			else:
				if self.on[i] == 1:
					pygame.draw.rect(screen, orange, [loc[0]+x, loc[1]+30, 25, 50])
					text=font.render(str(self.on[i]), True, white)
					screen.blit(text, [loc[0]+x, loc[1]+30])
					x+=25
				else:
					pygame.draw.rect(screen, gray, [loc[0]+x, loc[1]+30, 25, 50])
					text=font.render(str(self.on[i]), True, black)
					screen.blit(text, [loc[0]+x, loc[1]+30])
					x+=25
					
		pygame.draw.rect(screen, red, [loc[0], loc[1]+30, 195, 1]) #red vertical bar
		#white horizontal bars
		x=0
		for i in range(0, 8):
			if i%2 == 0:
				pygame.draw.rect(screen, white, [loc[0]+x, 1, 1, loc[1]+30])
				x+=30
			else:
				pygame.draw.rect(screen, white, [loc[0]+x, 1, 1, loc[1]+30])
				x+=25
			
			
	#animation
	def logic(self):		
		for i in range(0, 8):
			if self.val[i] == self.max+self.speed:
				self.on[i]=1
			else:
				self.on[i]=0
			if self.val[i] <= 0:
				continue
			if self.lock[i] == 0:
				self.val[i]-=self.speed
##########################end of class keys:
#draw: 195 pixels wide
#drawscratch: 50 pixels wide
		

hello=bmsreader.reader("bms/[BMS]ENERGY SYNERGY MATRIX/_another.bms")
# hello=bmsreader.reader("bms/[BMS]Acquire/_another.bms")

hello.readnote()
hello.arrangenote()

mykeys=keys(1)
p2keys=keys(1)

#default font
font=pygame.font.Font(None, 25)


count=0
		

j=0
k=0
x=0
xbuf=30

testnote=[[None for i in range(10)] for i in range(xbuf)]



'''
=====================================================================
'''

while not done:

	start_time = time.time()

	'''
event loop===========================================================
	'''
	
	pygame.event.pump()
	for i in pygame.event.get():
		if i.type == pygame.QUIT:	#close button
			done=True
		
		#player1
		if i.type == pygame.KEYDOWN:
			#lower key
			if i.key == pygame.K_z:
				mykeys.val[0]=mykeys.max+mykeys.speed
				mykeys.lock[0]=1
			if i.key == pygame.K_x:
				mykeys.val[2]=mykeys.max+mykeys.speed
				mykeys.lock[2]=1
			if i.key == pygame.K_c:
				mykeys.val[4]=mykeys.max+mykeys.speed
				mykeys.lock[4]=1
			if i.key == pygame.K_v:
				mykeys.val[6]=mykeys.max+mykeys.speed
				mykeys.lock[6]=1
			
				
				
			#upper key
			if i.key == pygame.K_s:
				mykeys.val[1]=mykeys.max+mykeys.speed
				mykeys.lock[1]=1
			if i.key == pygame.K_d:
				mykeys.val[3]=mykeys.max+mykeys.speed
				mykeys.lock[3]=1
			if i.key == pygame.K_f:
				mykeys.val[5]=mykeys.max+mykeys.speed
				mykeys.lock[5]=1
			
			#shift key
			if i.key == pygame.K_LSHIFT:
				mykeys.val[7]=mykeys.max+mykeys.speed
				mykeys.lock[7]=1
				
		if i.type == pygame.KEYUP:
			#lower key
			if i.key == pygame.K_z:
				mykeys.lock[0]=0
			if i.key == pygame.K_x:
				mykeys.lock[2]=0
			if i.key == pygame.K_c:
				mykeys.lock[4]=0
			if i.key == pygame.K_v:
				mykeys.lock[6]=0
			
				
				
			#upper key
			if i.key == pygame.K_s:
				mykeys.lock[1]=0
			if i.key == pygame.K_d:
				mykeys.lock[3]=0
			if i.key == pygame.K_f:
				mykeys.lock[5]=0
				
			#shift key
			if i.key == pygame.K_LSHIFT:
				mykeys.lock[7]=0
	
		
		#player2
		if i.type == pygame.KEYDOWN:
			#lower key
			if i.key == pygame.K_m:
				p2keys.val[0]=p2keys.max+p2keys.speed
				p2keys.lock[0]=1
			if i.key == pygame.K_COMMA:
				p2keys.val[2]=p2keys.max+p2keys.speed
				p2keys.lock[2]=1
			if i.key == pygame.K_PERIOD:
				p2keys.val[4]=p2keys.max+p2keys.speed
				p2keys.lock[4]=1
			if i.key == pygame.K_SLASH:
				p2keys.val[6]=p2keys.max+p2keys.speed
				p2keys.lock[6]=1
			
				
				
			#upper key
			if i.key == pygame.K_k:
				p2keys.val[1]=p2keys.max+p2keys.speed
				p2keys.lock[1]=1
			if i.key == pygame.K_l:
				p2keys.val[3]=p2keys.max+p2keys.speed
				p2keys.lock[3]=1
			if i.key == pygame.K_SEMICOLON:
				p2keys.val[5]=p2keys.max+p2keys.speed
				p2keys.lock[5]=1
			
			#shift key
			if i.key == pygame.K_RSHIFT:
				p2keys.val[7]=p2keys.max+p2keys.speed
				p2keys.lock[7]=1
				
		if i.type == pygame.KEYUP:
			#lower key
			if i.key == pygame.K_m:
				p2keys.lock[0]=0
			if i.key == pygame.K_COMMA:
				p2keys.lock[2]=0
			if i.key == pygame.K_PERIOD:
				p2keys.lock[4]=0
			if i.key == pygame.K_SLASH:
				p2keys.lock[6]=0
			
				
				
			#upper key
			if i.key == pygame.K_k:
				p2keys.lock[1]=0
			if i.key == pygame.K_l:
				p2keys.lock[3]=0
			if i.key == pygame.K_SEMICOLON:
				p2keys.lock[5]=0
				
			#shift key
			if i.key == pygame.K_RSHIFT:
				p2keys.lock[7]=0
			
	'''
game logic===========================================================
	'''	
	
	
		
	mykeys.logic()
	p2keys.logic()
	
	mykeys.draw(screen, [50, 150])
	mykeys.drawunder(screen, font, [50, 150])
	mykeys.drawscratch(screen, [50, 150])
	
	p2keys.draw(screen, [609, 150])
	p2keys.drawunder(screen, font, [609, 150])
	p2keys.drawscratch(screen, [854, 150])
	
	
	
	
	'''
draw loop============================================================
	'''


	arr=hello.drawnote(j, k)
	#print(arr, j, k)
	k+=2
	if k > 384:
		k=0
		j+=1
	if x >= xbuf - 1:
		x=0


	for i in range(10):
		if arr[i] != "00":
			if i == 0:
				testnote[x][i]=note(black, arr[i], [0, 0, 0, 0]) #bar
			if i == 1:
				testnote[x][i]=note(gray, arr[i], [50, 0, 30, 7]) #white1
			if i == 2:
				testnote[x][i]=note(blue, arr[i], [80, 0, 25, 7]) #blue1
			if i == 3:
				testnote[x][i]=note(gray, arr[i], [105, 0, 30, 7]) #white2
			if i == 4:
				testnote[x][i]=note(blue, arr[i], [135, 0, 25, 7]) #blue2
			if i == 5:
				testnote[x][i]=note(gray, arr[i], [160, 0, 30, 7]) #white3
			if i == 6:
				testnote[x][i]=note(blue, arr[i], [190, 0, 25, 7]) #blue3
			if i == 7:
				testnote[x][i]=note(gray, arr[i], [215, 0, 30, 7]) #white4
			if i == 8:
				testnote[x][i]=note(red, arr[i], [0, 0, 50, 7]) #scratch

	#print notes
	for a in range(xbuf):
		curframe = []
		if testnote[a][0]:
			if testnote[a][0].playmusic():
				try:
					curframe.append(hello.WAV[testnote[a][0].str])
				except:
					pass
		for i in range(1, 10):
			if testnote[a][i]:
				testnote[a][i].printnote()
				if testnote[a][i].playmusic():
					try:
						curframe.append(hello.WAV[testnote[a][i].str])
					except:
						pass
					if i <9:
						mykeys.val[i-1]=mykeys.max+mykeys.speed
						mykeys.lock[i-1]=1
				else:
					if i <9:
						mykeys.lock[i-1]=0
					
		for ff in curframe:
			ff.play()
					

	#move notes
	for a in range(xbuf):
		for i in range(10):
			if testnote[a][i]:
				testnote[a][i].loc[1]+=6


	x+=1

	for i in range(0, 7):
		text=font.render(str(mykeys.on[i]), True, white)
		screen.blit(text, [width-200+25*i, height-30])
	
	
	'''
final render=========================================================
	'''
	test=(60.0/(hello.BPM/4))/215.0*1000.0 #master
	pygame.display.flip() #update frame
	
	timetosleep = test/1000.0 - (time.time() - start_time)
	if timetosleep > 0:
		# print("slept " + str(timetosleep) + " seconds")
		time.sleep(timetosleep)
	
	screen.fill(black) #clear screen AFTER clock.tick wait

pygame.quit() #hangs on IDLE if it isnt here.

