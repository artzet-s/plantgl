
from openalea.oalab.gui.control import AbstractControlWidget
from openalea.oalab.plugins.controls.painters import PainterColorList, PainterInterfaceObject

from openalea.plantgl.gui.materialeditor import MaterialEditor
from openalea.plantgl.all import PglTurtle

def to_color(material_list):
    """
    Material(name='C0', ambient=Color3(65,45,15)) -> ('C0', (65,45,15))
    """
    color_list = []
    for material in material_list:
        a = material.ambient
        color = (material.name, (a.red, a.green, a.blue))
        color_list.append(color)
    return color_list

def to_material(color_list):
    """
    ('C0', (65,45,15)) -> Material(name='C0', ambient=Color3(65,45,15))
    """

    from openalea.plantgl.all import Material, Color3
    material_list = []
    for color in color_list:
        material = Material(color[0], Color3(*color[1][:3]))
        material_list.append(material)
    return material_list


class ColorListWidget(MaterialEditor, AbstractControlWidget):

    def __init__(self):
        AbstractControlWidget.__init__(self)
        MaterialEditor.__init__(self, parent=None)

        # Signal used by "autoapply" method
        self.value_changed_signal = 'valueChanged()'

    def reset(self, value=[], **kwargs):
        self.setValue(value)

    def value(self):
        material_list = self.getTurtle().getColorList()
        return to_color(material_list)

    def setValue(self, value):
        turtle = PglTurtle()
        turtle.clearColorList()
        for color in to_material(value):
            turtle.appendMaterial(color)
        self.setTurtle(turtle)

    @classmethod
    def paint(self, control, shape=None):
        if shape == 'hline':
            return PainterColorList()


from openalea.plantgl.gui.curve2deditor import Curve2DEditor
class Curve2DWidget(Curve2DEditor, AbstractControlWidget):
    def __init__(self):
        AbstractControlWidget.__init__(self)
        Curve2DEditor.__init__(self, parent=None)

    def reset(self, value=None, **kwargs):
        if value is None:
            value = self.newDefaultCurve()
        self.setValue(value)

    def value(self):
        return self.curveshape.geometry

    def setValue(self, value):
        self.setCurve(value)

    @classmethod
    def paint(self, control, shape=None):
        if shape == 'hline':
            return PainterInterfaceObject()
