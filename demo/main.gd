extends Node2D

@onready var rot1 = $Rotator1
@onready var rot2 = $Rotator2

func _ready() -> void:
	# Set up the next_rotator paths
	rot1.next_rotator = rot2.get_path()
	rot2.next_rotator = rot1.get_path()

	# Ensure initial states
	rot1.play()  # start the first rotator
	rot2.pause() # second rotator starts paused
