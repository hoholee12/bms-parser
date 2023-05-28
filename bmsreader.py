#!/usr/bin/env python
import pygame.mixer
import pygame
import threading
import time

mixer=pygame.mixer
mixer.init()

class player(threading.Thread):
	def __init__(self, WAV, NUM, BPM, MPLAY, loop, bms, filename, count, i):
		threading.Thread.__init__(self)
		self.WAV=WAV
		self.NUM=NUM
		self.BPM=BPM
		self.MPLAY=MPLAY
		self.loop=loop
		self.bms=bms
		self.filename=filename
		self.count=count
		self.i=i


	def run(self):
		x=(60/(self.BPM/4))/192*1000+0.5 #master
		for k in range(0, 384, 2):
			for j in range(9):
				if self.MPLAY[self.i][j][k:k+2] != "" and self.MPLAY[self.i][j][k:k+2] != "00":
					self.WAV[self.MPLAY[self.i][j][k:k+2]].play()
					print("osim:"+self.MPLAY[self.i][j][k:k+2]+" "+str(self.i)+" "+str(j)+" "+str(k))
			#if self.MPLAY[self.i][9][k:k+2] != "" and self.MPLAY[self.i][9][k:k+2] != "00" and self.MPLAY[self.i][9][k:k+2] != "F0":
			#	print("hello")
			#	self.WAV[self.MPLAY[self.i][9][k:k+2]].play()

			time.sleep(x/1000.0) #140bpm



class reader:
	WAV={}
	NUM=[]
	BPM=None
	PLAY=[["" for i in range(10)] for i in range(100)]
	MPLAY=[["" for i in range(10)] for i in range(100)]
	loop=-1
	bms=None
	filename=None
	count=[[0 for i in range(10)] for i in range(100)]
	def __init__(self, filename):
		self.filename=filename
		self.bms=open(self.filename, 'r')
		for i in self.bms.read().split('\n'):
			if i[:1] == '#':
				if i[1:4] == "WAV":
					try:
						self.WAV[i[4:6]]=mixer.Sound(self.filename.rsplit('/', 1)[0]+'/'+i.split(' ')[1])
					except:
						self.WAV[i[4:6]]=mixer.Sound(self.filename.rsplit('/', 1)[0]+'/'+i.split(' ')[1].split('.')[0]+".ogg")
						
				if i[1:4] == "BPM":
					self.BPM=int(i.split(' ')[1])
					
					
				try:
					if int(i[1:4]):
						self.NUM.append(i.split(':')[0])
				except:
					pass
		#read everything here first, then close file
		
		
		
	def readnote(self):
		diff=None
		self.bms.seek(0)
		for i in self.bms.read().split('\n'):
			if i[:1] == '#':
				if i[1:4].isnumeric():
					if i[1:4] != diff:
						diff=i[1:4]
						self.loop=int(diff)
					if i[4:6] == "01": #autoplay
						self.PLAY[self.loop][0]=i[7:]
						self.count[self.loop][0]=len(str(self.PLAY[self.loop][0]))
						print("0:"+str(self.PLAY[self.loop][0]))
					elif i[4:6] == "04": #bga
						self.PLAY[self.loop][9]=i[7:]
						self.count[self.loop][9]=len(str(self.PLAY[self.loop][9]))
						print("0:"+str(self.PLAY[self.loop][9]))
					elif i[4:6] == "11": #whitekey 1
						self.PLAY[self.loop][1]=i[7:]
						self.count[self.loop][1]=len(str(self.PLAY[self.loop][1]))
						print("1:"+str(self.PLAY[self.loop][1]))
					elif i[4:6] == "12": #bluekey 1
						self.PLAY[self.loop][2]=i[7:]
						self.count[self.loop][2]=len(str(self.PLAY[self.loop][2]))
						print("2:"+str(self.PLAY[self.loop][2]))
					elif i[4:6] == "13": #whitekey 2
						self.PLAY[self.loop][3]=i[7:]
						self.count[self.loop][3]=len(str(self.PLAY[self.loop][3]))
						print("3:"+str(self.PLAY[self.loop][3]))
					elif i[4:6] == "14": #bluekey 2
						self.PLAY[self.loop][4]=i[7:]
						self.count[self.loop][4]=len(str(self.PLAY[self.loop][4]))
						print("4:"+str(self.PLAY[self.loop][4]))
					elif i[4:6] == "15": #whitekey 3
						self.PLAY[self.loop][5]=i[7:]
						self.count[self.loop][5]=len(str(self.PLAY[self.loop][5]))
						print("5:"+str(self.PLAY[self.loop][5]))
					elif i[4:6] == "18": #bluekey 3
						self.PLAY[self.loop][6]=i[7:]
						self.count[self.loop][6]=len(str(self.PLAY[self.loop][6]))
						print("6:"+str(self.PLAY[self.loop][6]))
					elif i[4:6] == "19": #whitekey 4
						self.PLAY[self.loop][7]=i[7:]
						self.count[self.loop][7]=len(str(self.PLAY[self.loop][7]))
						print("7:"+str(self.PLAY[self.loop][7]))
					elif i[4:6] == "16": #scratch
						self.PLAY[self.loop][8]=i[7:]
						self.count[self.loop][8]=len(str(self.PLAY[self.loop][8]))
						print("8:"+str(self.PLAY[self.loop][8]))
					print(self.loop, diff, self.count[self.loop])
		print("end")


	def arrangenote(self):
		j=0
		l=0
		for i in range(0, self.loop+1):
			for j in range(10):
				if self.count[i][j] != 0:
					l=0 #init
					for k in range(192):
						if int(192/(self.count[i][j]/2)*(l/2)) == k:
							self.MPLAY[i][j]+=self.PLAY[i][j][l:l+2]
							l+=2
						else:
							self.MPLAY[i][j]+="00"
				else:
					for k in range(192):
						self.MPLAY[i][j]+="00"
				print(str(i), str(j), str(l), self.MPLAY[i][j])


	def drawnote(self, i, k):
		arr=["" for x in range(10)]
		for j in range(10):
			if self.MPLAY[i][j][k:k+2] != "" and self.MPLAY[i][j][k:k+2] != "00" and self.MPLAY[i][j][k:k+2] != "01":
				arr[j]=self.MPLAY[i][j][k:k+2]
			else:
				arr[j]="00"
		return arr







	def playnote(self):
		i=0
		PLAYTHREAD=None
		x=(60/(self.BPM/4))*1000+0.5 #master
		for i in range(0, self.loop+1):
			PLAYTHREAD=player(self.WAV, self.NUM, self.BPM, self.MPLAY, self.loop, self.bms, self.filename, self.count, i)
			PLAYTHREAD.start()
			print(x)
			time.sleep(x/1000.0) #140bpm




			
if __name__ == "__main__":
				
	hello=reader("bms/Release The Music/#Release The Music [03 SP ANOTHER].bme")
	hello.readnote()
	hello.arrangenote()

	hello.playnote()






#sleep=int((60/(bpm/4))/192*1000+0.5)

