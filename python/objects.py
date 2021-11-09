from constants import body_2_color

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

    @staticmethod
    def collide(r1, r2):
        x_collide = (r1.left() < r2.left() and r1.right() > r2.left()) or (r1.left() > r2.left() and r2.left() < r2.right())
        y_collide = (r1.top() < r2.bottom() and r1.bottom() > r2.top()) or (r1.top() > r2.top() and r2.top() < r2.bottom())
        return x_collide and y_collide

class Drawable():

    def draw(self, surface):
        raise "Implement this method"

class MovingBox(Rect, Drawable):

    def __init__(self, x, y, w, h) -> None:
        super().__init__(x, y, w, h)

    def draw(self, surface):
        pygame.draw.rect(surface, body_2_color, (self.x, self.y, self.w, self.h))
