# Arduino Step Sequencer

### Features

**(Required)**

- Sequence MIDI devices

- Change tempo with Rate Knob

- Change time division with Knob 2

- Transmit MIDI CC on Knob 3 & 4

**(Desired)**

- Sequence multiple devices simultaneously

- Sync with USB for start/stop and tempo

- Store at least the last sequence

- Tap Tempo

- Variable Sequence Length

- Change octaves

- Accidentals using Shift Button

- Performance Mode

### Button Layout

```
+------------+
|(t)(l)(c)(c)| <-- Knobs
+------------+
|[r][p][T][s]| <-- Buttons
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

`r` - Record (Clear Sequence)

`p` - Play/Pause Sequence

`T` - Tap tempo (Rest)

`s` - (Shift)

`d` - Octave down

`u` - Octave up

`b` - Prev Page (Reduce Sequence)

`n` - Next Page (Extend Sequence)

`1-8` - Steps/Keys



### Workflow

**Record Sequence:**

`[ Press Record ] -> [ Press Key Button to Add Step] -> [ Press Record to Stop ]`

Sequence buttons light up to show sequence progress.



**Play Sequence:**

`[ Press Play ] -> [ Sequence Plays ] -> [ Press Play ] -> [ Sequence Stops ]`

Each step lights as it plays. Play light stays on while sequence is playing.



**Performance Mode**

`[ No Sequence Playing ] -> [ Press Key ] -> [ Transmit Note ]`


