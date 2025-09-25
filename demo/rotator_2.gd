extends Pseudo3DRotatingSprite

@export var next_rotator: NodePath
@onready var next_node = get_node(next_rotator)

func _ready() -> void:
	pause()
	# Godot 4 style signal connection
	connect("rotation_completed", Callable(self, "_on_rotation_completed"))

func _on_rotation_completed() -> void:
	pause()
	if next_node:
		next_node.play()
