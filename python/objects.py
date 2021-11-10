from constants import body_2_color, width, height, multiplier

import pygame


class Rect():

    def __init__(self, x, y, w, h) -> None:
        self.x = x
        self.y = y
        self.w = w
        self.h = h

    def left(self):
        return self.x
    
    def right(self):
        return self.x + self.w

    def top(self):
        return self.y

    def bottom(self):
        return self.y + self.h


class Drawable():

    def draw(self, surface):
        raise "Implement this method"

class GameObject():

    def update(self):
        raise "Implement this method"

class Collision(Rect):

    def collide(self, rect):
        raise "Implement this method"

    @staticmethod
    def check(r1, r2):
        return r1.left() < r2.right() and \
               r1.right() > r2.left() and \
               r1.top() < r2.bottom() and \
               r1.bottom() > r2.top()
        

class MovingBox(Rect, Drawable, GameObject):

    def __init__(self, x, y, w, h, dx=0, dy=0, color=body_2_color):
        super().__init__(x, y, w, h)
        self.dx = dx
        self.dy = dy
        self.color = color

    def draw(self, surface):
        pygame.draw.rect(surface, self.color, (self.x * multiplier, self.y * multiplier, self.w * multiplier, self.h * multiplier))

    def update(self):
        self.x = (self.x + self.dx + self.w // 2) % width - self.w // 2
        self.y = (self.y + self.dy + self.h // 2) % height - self.h // 2