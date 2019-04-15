# Arduino Step Sequencer

Hardware MIDI sequencer adapted from the Adafruit [Mini UNTZtrument](https://learn.adafruit.com/mini-untztrument-3d-printed-midi-controller/overview) project. The case is 3D printed and based around a Seeeduino Lite. There are only 16 buttons so the controls are a bit creative using the shift button. 

## Features

**(Required)**

- [x] Sequence MIDI devices
- [x] Change tempo with Rate Knob
- [ ] Change time division with Knob 2
- [ ] Transmit MIDI CC on Knob 3 & 4

**(Desired)**

- [ ] Sequence multiple devices simultaneously
- [ ] Sync with USB for start/stop and tempo
- [ ] Send Play over MIDI for external devices
- [ ] Store at least the last sequence
- [ ] Tap Tempo
- [ ] Variable Sequence Length
- [ ] Change octaves
- [ ] Accidentals using Shift Button
- [x] Performance Mode
- [ ] Remove Last Step
- [ ] Edit Step
- [ ] Gate length on Knob 3
- [ ] Swing on Knob 4
- [ ] Add switch for internal/USB/external sync

## Button Layout

```
+------------+
|(t)(l)(c)(c)| <-- Knobs
+------------+
|[p][r][T][s]| <-- Buttons
|[d][u][b][n]|
|[1][2][3][4]|
|[5][6][7][8]|
+------------+
```

**Legend**

`t` - Rate

`l` - Time Division

`c` - MIDI CC

`k` - Undefined knob

`p` - Play/Pause Sequence

`r` - Record (Clear Sequence)

`T` - Tap tempo (Rest)

`s` - (Shift)

`d` - Octave down (Toggle sync mode)

`u` - Octave up (Toggle Knob mode)

`b` - Prev Page (Reduce Sequence)

`n` - Next Page (Extend Sequence)

`1-8` - Steps/Keys (MIDI Channel?)



## Workflow

**Record Sequence:**

`[ Press Record ] -> [ Press Key Button to Add Step] -> [ Press Record to Stop ]`

Sequence buttons light up to show sequence progress.



**Play Sequence:**

`[ Press Play ] -> [ Sequence Plays ] -> [ Press Play ] -> [ Sequence Stops ]`

Each step lights as it plays. Play light stays on while sequence is playing.



**Performance Mode**

`[ No Sequence Playing ] -> [ Press Key ] -> [ Transmit Note ]`


