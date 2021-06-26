#!/bin/bash
set -uex

# Top directory
cd $(dirname $0)
GIT_DIR=$(git rev-parse --show-toplevel)
echo $GIT_DIR

# Create script directory
SOUNDS_DIR=$GIT_DIR/sounds
mkdir -p $SOUNDS_DIR

# Fetch wav files
wget -P $SOUNDS_DIR https://www2.cs.uic.edu/~i101/SoundFiles/BabyElephantWalk60.wav
wget -P $SOUNDS_DIR https://www2.cs.uic.edu/~i101/SoundFiles/CantinaBand60.wav
wget -P $SOUNDS_DIR https://www2.cs.uic.edu/~i101/SoundFiles/Fanfare60.wav
wget -P $SOUNDS_DIR https://www2.cs.uic.edu/~i101/SoundFiles/ImperialMarch60.wav
wget -P $SOUNDS_DIR https://www2.cs.uic.edu/~i101/SoundFiles/PinkPanther60.wav
wget -P $SOUNDS_DIR https://www2.cs.uic.edu/~i101/SoundFiles/StarWars60.wav
