import sys
import time
import pygame
import pygame.gfxdraw


from drawingEngine import Engine


a = Engine("a") # корень

b = a.addChild("b")
e = a.addChild("e")
h = a.addChild("h")

c = b.addChild("c")
d = b.addChild("d")

f = e.addChild("f")
g = e.addChild("g")

i = h.addChild("i")
j = h.addChild("j")
k = h.addChild("k")


a.walker(0.5)


# print("Node:\t    x,\ty")
for node in a.nodes:
    p = node.position(origin=(0, 0), scalex=100, scaley=1)
    print("%s:\t(%#4d,\t%d)" % (node.data, p[0], p[1]))


width, height = 1000, 500
sizex, sizey = 130, 60
rootpos = (width / 2 - 100, height / 2 - 100)


pygame.init()
screen = pygame.display.set_mode((width, height))
pygame.display.set_caption('')
background = pygame.Surface(screen.get_size())
background = background.convert()
background.fill((250, 250, 250))
screen.blit(background, (0, 0))


for node in a.nodes:
    if node.parent:
        pygame.draw.aaline(
            screen, (0, 0, 0), node.position(
                rootpos, sizex, sizey), node.parent.position(
                rootpos, sizex, sizey))


for node in a.nodes:

    myfont = pygame.font.Font(None, 36)
    label = myfont.render(node.data, 1, (0, 0, 0))
    textrect = label.get_rect()
    textrect.centerx = node.position(rootpos, sizex, sizey)[0]
    textrect.centery = node.position(rootpos, sizex, sizey)[1]

    p = textrect.copy().inflate(10, 10)
    pygame.draw.ellipse(screen, (255, 255, 255), p)
    pygame.gfxdraw.aaellipse(screen, p.centerx, p.centery, int(
        p.width / 2), int(p.height / 2), (0, 255, 255))

    screen.blit(label, textrect)


pygame.display.flip()


while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT or event.type == pygame.KEYDOWN and event.unicode in ['\x1b', 'q']:
            pygame.display.quit()
            pygame.quit()
            sys.exit()
    time.sleep(0.1)
