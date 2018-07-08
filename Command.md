# Command Structure
`^<command id><Command><Target><Args>$`

`<command id> - global id of current command, id will increase after a success command procedure.`

`<Command>    - Operation`

`<Target>     - operate target`

`<Args>       - operation args, handled by target`

## Command
W - Write.

R - Read.

E - Return, alias echo

### Write Command
After a valid write command is given by host, the client will handle this command, and the host will wait for <timeout>.
<timeout> can be set by user (not recommanded). If a report was not given by client within <timeout>, host will resent 
last command. If it is failed after 3 trails, host report operation failure to user.

### Read Command
After a valid read command is given by host, a valid return should be given by the client with in <timeout>. If there is
not any return with in <timeout>, host will retry to send the last command. If it is still fail to receive the return for
3 trails, host will report operation failure to user.

## Return(Echo)
_Return to READ command:_ `^E<command id>V"<return value>"$`
_Return to WRITE command:_ 
1. Success: `^E<command id>O$`
2. Failed: `^E<command id>F$`

## Target
M - Movement.

S - Servo.

G - GPIO.

U - Sonar(Ultrasonic).

L - Label, alias Marker

## Movement 
### Args
_Format_ `^<command id><command>M<type>X"<X value>"Y<Y value>"Z<Z value>"$`


`<command>`: command type, generally can be 'R' or 'W', but 'R' is not used.
`<type>` indicates movement type, can be relative or speed.
    1. If <type> = R, trite movement value as relative movement, that is move distance given
	    by values.
	2. If <type> = V, trite movement value as speed, that is, move with speed given by values.
`<value>` is between -1.0 and 1.0, indicating wheel rotation direction and speed.

## Servo
### Args
_Format(Read Servo):_ `^<command id>RS$`
_Format(Write Servo):_ `^<command id>WS"<value>"$`
`<value` is between 0 and 360, indicating orientation.

## GPIO
*Format:* `^<command id><command>GC<Channel>B<Bank>P<Port>""<Value>""$`
<Channel> - Channel, tracker is 0, ex is 1.
<Bank>    - Bank, can be A or B.
<Port>    - Port number, between 0 and 7 (included).
<Value>   - Value of the target port, can be 0 or 1.

## Sonar
Sonar is not writabel.

## Label
Read or Set label value

*Format(Read Marker):* `^<command id>RL`
*Format(Write Marker):* `^<command id>WL"<bit0>,<bit1>,...,<bit15>"$`

`^`
# Examples
## Set Servo to 270 degree
`^7WS270$`

## Set Channel 1 bank B port 7 to low
`^8WGC1BBP7"0"$`

## Read tracker 
### Read tracker 1 port 3
tracker 1 is on channel 0, bank A
host send: `^9RGC1BAP3$`
client reply: `^E9V1$`

### Read tracker 2 port 2
tracker 2 is on channel 0, bank A
host send: `^12RGC1BAP5$`
client reply: `^E12V0$`

## Set Movement
### Forward purely(voloity)
`^13MVX"0.0"Y"0.5"Z"0.0"$`
### Mixed motion(distance)
`^14MRX0.2Y-0.76Z-0.1$`

## Read Sonar
host send: `^15RU$`
client reply: `^E15V79.55$`

## Read Servo
host send: `^16RS$`
client reply: `^E16V270$`


# Lower communacation
!id=<devide id>,<message>#
