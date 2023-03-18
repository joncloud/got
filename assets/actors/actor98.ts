const pic = [...Buffer.from('Dw8PD0pKS00PDw8PDw8PDw8PD0pLS0xNTw8PDw8PDw8PD0pLS0xNTU5PDw8PDw8PD0pLS0xMTU1OTx4PDw8PDw8jISIjJCYnKCkqDw8PDw8PIzc3NzckJSYnKg8PDw8PDyM3Nzc3NyQlJioPDw8PDw8jITc3Nzc3JCUqDw8PDw8PDyMhNzc3NyMqDw8PDw8PDw/JIyE3NyMq0g8PDw8PDw/JxUknIyMqSczSDw8PDw8PzMlISSoqSUzS1A8PDw8PDw9KSUpLS0xMSw8PDw8PDw8PzcjJ0tXLzNUPDw8PDw8PD0tISE1PS0tPDw8PDw8PDw9LSUlNT0xMTw8PDw8PDw8PDw9KSktNDw8PDw8PDw8PDw9KS0tMTU8PDw8PDw8PDw9KS0tMTU1OTw8PDw8PDw9KS0tMTE1NTk8eDw8PDw8PIyEiIyQmJygpKg8PDw8PDyM3Nzc3NyUmJykqDw8PDw8PIyE3Nzc3JCcoKg8PDw8PDw8jITc3NzcmJyoPDw8PDw8PIyE3Nzc3IyoPDw8PDw8PycwmITc3IyoPDw8PDw8PycVISScjIypMDw8PDw8PzMXJSEhJKipMSw8PDw8PDw/JSklKSktLTEsPDw8PDw8PD0tISErVy8zVDw8PDw8PDw8PDw8PT0tLTw8PDw8PDw8PDw8PD01MTE8PDw8PDw8PDw8PSkpLTQ8PDw8PDw8PDw8PSktLTE1PDw8PDw8PDw8PSktLTE1NTk8PDw8PDw8PSktLTExNTU5PHg8PDw8PDyMhIiMkJicoKSoPDw8PDw8jNzc3NyQlJicqDw8PDw8PIzc3Nzc3JCUmKg8PDw8PDyMhNzc3NzckJSoPDw8PDw8PIyE3Nzc3IyoPDw8PDw8PD8kjITc3IyrSDw8PDw8PD8nFSScjIypJzNIPDw8PDw/MyUhJKipJTNLUDw8PDw8PD0pJSktLTExLDw8PDw8PDw/NyMnS1cvM1Q8PDw8PDw8PS0hITU9LS08PDw8PDw8PD0tJSU1PTExPDw8PDw8PDw8PD0pKS00PDw8PDw8PDw8PD0pLS0xNTw8PDw8PDw8PD0pLS0xNTU5PDw8PDw8PD0pLS0xMTU1OTx4PDw8PDw8jISIjJCYnKCkqDw8PDw8jITc3NzckJicoKg8PDw8PIyE3Nzc3NyYmKg8PDw8PDyMhNzc3NzclKg8PDw8PDw8PIyE3Nzc3IyoPDw8PDw8PDw8mITc3IypL0g8PDw8PDw8PSScjIypMSMzSDw8PDw8PD0hJKipMS0lMzNIPDw8PDw9KSUpLS0xMS9IPDw8PDw8PzcjJ0kpISEoPDw8PDw8PD0tISE0PDw8PDw8PDw8PDw9LSUlNDw8PDw8PDw8PDw8PDw9KSktNDw8PDw8PDw8PDw9KS0tMTU8PDw8PDw8PDw9KS0tMTU1OTw8PDw8PDw9KS0tMTE1NTk8eDw8PDw8PIyQlyMnKyiUmKg8PDw8PDyM3yR/FxR/KJCoPDw8PDw8jN8jFx8jFyCQqDw8PDw8PIyE3NyMkNzcjKg8PDw8PDw8jITcfHzcjKg8PDw8PDw8PySMhNzcjKtIPDw8PDw8PycVJJyMjKknM0g8PDw8PzMXJSEkqKklMzszSDw8PDw/JSklKS0tMTEvSDw8PDw8PD83IydLVy8zVDw8PDw8PDw9LSEhNT0tLTw8PDw8PDw8PS0lJTU9MTE8PDw8PDw8PDw8PSkpLTQ8PDw8PDw8PDw8PSktLTE1PDw8PDw8PDw8PSktLTE1NTk8PDw8PDw8PSktLTExNTU5PHg8PDw8PDyMlyMnKyiQlJioPDw8PDw8jyR/FxR/KNyQqDw8PDw8PI8jFx8jFyDckKg8PDw8PDyM3NyIkNzc3IyoPDw8PDw8PITc3HzcjIyoPDw8PDw8PDyMhNzcjKirSDw8PDw8PD8nNJyMjKklJzNIPDw8PD8zFTEkqKknOzMzSDw8PDw8PyUpJSktLTNLT1A8PDw8PDw9LSUlM1cvM1Q8PDw8PDw8PDw8PD09LS08PDw8PDw8PDw8PDw9NTExPDw8PDw8PDw8PD0pKS00PDw8PDw8PDw8PD0pLS0xNTw8PDw8PDw8PD0pLS0xNTU5PDw8PDw8PD0pLS0xMTU1OTx4PDw8PDw8jJCXIycrKJSYqDw8PDw8PIzfJH8XFH8okKg8PDw8PDyM3yMXHyMXIJCoPDw8PDw8jITc3IiQ3NyMqDw8PDw8PDyMhNx8fNyMqDw8PDw8PDw/JIyE3NyMq0g8PDw8PDw/JxUknIyMqSczSDw8PDw/MxclISSoqSUzOzNIPDw8PD8lKSUpLS0xMS9IPDw8PDw8PzcjJ0tXLzNUPDw8PDw8PD0tISE1PS0tPDw8PDw8PDw9LSUlNT0xMTw8PDw8PDw8PDw9KSktNDw8PDw8PDw8PDw9KS0tMTU8PDw8PDw8PDw9KS0tMTU1OTw8PDw8PDw9KS0tMTE1NTk8eDw8PDw8PIyQlJsnKysslKg8PDw8PDyMhN8kfxcUfyyoPDw8PDw8jITfIxcfIxckqDw8PDw8PIyE3NzciJDcjKg8PDw8PDw8jISE3Hzc3Kg8PDw8PDw8PySMjITc3IyoPDw8PDw8PycVJSScjIyrM0g8PDw8PD8nFxclJKipJTMzSDw8PDw/My8xKS0tMTEvSDw8PDw8PD83IydJPS0tPDw8PDw8PDw9LSEhNDw8PDw8PDw8PDw8PS0lJTQ8PDw8PDw8PDw8PDw8PDw9KTEwPDw8PDw8PDw8PDw9LS0xNTQ8PDw8PDw8PDw9LS0xNTU5PDw8PDw8PDw9KS0xMTU1OTx4PDw8PDw8PLCwpKCgnJiUjDw8PDw8PD8sfycklJCMiIw8PDw8PD8vJyMfFJCUhNyMPDw8PDw8PJSQjIiIhNzchIw8PDw8PDx8fIiE3Nzc3ISMPDw8PDw8nIiMsLCwrKikPDw8PDw8pJSQsS89NTEsPDw8PDw8PKyzQzczKTUxLDw8PDw8PDw9NTEtLS0pJSg8PDw8PDw8PD8vJyM1JTA8PDw8PDw8PDw9LSUpLTA8PDw8PDw8PDw9MS0pJS0wPDw8PDw8PDw8PDw8PSkxMDw8PDw8PDw8PDw8PS0tMTU0PDw8PDw8PDw8PS0tMTU1OTw8PDw8PDw8PSktMTE1NTk8eDw8PDw8PDywsKSgoJyYlIw8PDw8PDw/Iyx/KJCMiNyEjDw8PDw8PzcnFx8ohNzc3ISMPDw8PDyUjIjc3Nzc3NyEjDw8PDw8fHyEhJSwsKyknDw8PDw8PJyElLCxMTE0PDw8PDw8PKSUlLUtMz0xLDw8PDw8PDyssLE3QzczKSw8PDw8PDw8PTUxLS0tKSUoPDw8PDw8P0s3MzU3VzMvVTA8PDw8PS0pJS00PD01JSktMDw8PS0pJS00PD01LSklLTA8PDw8PDw8PD0pMTA8PDw8PDw8PDw8PD0tLTE1NDw8PDw8PDw8PD0tLTE1NTk8PDw8PDw8PD0pLTExNTU5PHg8PDw8PDw8sLCkoKCcmJSMjDw8PDw8Pyx/JySUkIyIhISMPDw8Py8nIx8UkJSE3NyEjDw8PDw8lJCMiIjc3NyEnDw8PDw8PHx8iITc3IScnDw8PDw8PDyciIywsLCtNDw8PDw8PDyklLC1Lz01MSw8PDw8PDw8sTtDNzMpNTEsPDw8PDw8PD01MS0tLSklKDw8PDw8PDw8Py8nIzUlMDw8PDw8PDw8PD0tJSktMDw8PDw8PDw8PD0xLSklLTA8PDw8PDw8PDw8PDw9KTEwPDw8PDw8PDw8PDw9LS0xNTQ8PDw8PDw8PDw9LS0xNTU5PDw8PDw8PDw9KS0xMTU1OTx4PDw8PDw8PLCwpKCgnJiUjDw8PDw8PDx/JyiUkIyI3ISMPDw8PDw/KxyIjIiE3NzchIw8PDw8PJSMiNzc3Nzc3ISMPDw8PDx8hISElLCwrKScPDw8PDw8nIiksLE5NTQ8PDw8PDw8pJClNz05NTEsPDw8PDw8PK9DNzMpOTUxLDw8PDw8PDw9NTEtLS0pJSg8PDw8PDw/SzczNTdXMy9VMDw8PDw9LSklLTQ8PTUlKS0wPDw9LSklLTQ8PTUtKSUtMDw8PDw8PDw9KTEwPDw8PDw8PDw8PDw9LS0xNTQ8PDw8PDw8PDw9LS0xNTU5PDw8PDw8PDw9KS0xMTU1OTx4PDw8PDw8PIyUmJygoKSwsDw8PDw8PDyMiIyQlyckfyw8PDw8PDw8jNyElJMXHyMnLDw8PDw8jITc3ISIiIyQlDw8PDw8PIyE3Nzc3ISIfHw8PDw8PDw8pKissLCwjIicPDw8PDw8PD0tMTc9LLCQlKQ8PDw8PDw9LTE3KzM3QLCsPDw8PDw8PSklKS0tLTE8PDw8PDw8PDw9MSc3IycsPDw8PDw8PDw8PD0tLSklMDw8PDw8PDw8PDw9LS0lKS0wPDw8PDw8PDw8PSkxMDw8PDw8PDw8PDw8PS0tMTU0PDw8PDw8PDw8PS0tMTE1OTw8PDw8PDw8PSktLTE1NTk8eDw8PDw8PDyMlJicoKCksLA8PDw8PDyMhNyIjJMofy8gPDw8PDyMhNzc3IcrHxcnNDw8PDw8jITc3Nzc3NyIjJQ8PDw8PDycpKywsJSEhHx8PDw8PDw8PD01MTCwsJSEnDw8PDw8PDw9LTM9MSy0lJSkPDw8PDw8PS8rMzdBNLCwrDw8PDw8PD0pJSktLS0xPDw8PDw8PD0vVy8zVT83MzdIPDw8PD0tLSklMDw9LS0lKTA8PDw9LS0lKS0wPD0tLSUpMDw8PDw8PD0pMTA8PDw8PDw8PDw8PD0tLTE1NDw8PDw8PDw8PD0tLTE1NTk8PDw8PDw8PD0pLTExNTU5PHg8PDw8PDyMjJSYnKCgpLCwPDw8PDyMhISIjJCXJyR/LDw8PDw8jITc3ISUkxcfIycsPDw8PDychNzc3IiIjJCUPDw8PDw8PJychNzchIh8fDw8PDw8PDw9NKywsLCMiJw8PDw8PDw8PS0xNz0stLCUpDw8PDw8PD0tMTcrMzdBOLA8PDw8PDw9KSUpLS0tMTw8PDw8PDw8PD0xJzcjJyw8PDw8PDw8PDw8PS0tKSUwPDw8PDw8PDw8PD0tLSUpLTA8PDw8PDw8PDw9KTEwPDw8PDw8PDw8PDw9LS0xNTQ8PDw8PDw8PDw9LS0xNTU5PDw8PDw8PDw9KS0xMTU1OTx4PDw8PDw8PIyUmJygoKSwsDw8PDw8PIyE3IiMkJcrJHw8PDw8PIyE3NzchIiMix8oPDw8PDyMhNzc3Nzc3IiMlDw8PDw8PJykrLCwlISEhHw8PDw8PDw8PTU1OLCwpIicPDw8PDw8PD0tMTU7PTykkKQ8PDw8PDw9LTE1OyszN0CsPDw8PDw8PSklKS0tLTE8PDw8PDw8PS9XLzNVPzczN0g8PDw8PS0tKSUwPD0tLSUpMDw8PD0tLSUpLTA8PS0tJSkwPDw==', 'base64')] as const;
const shot = [...Buffer.from('AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA==', 'base64')] as const;

const actor_info = {
  move: 0,
  width: 16,
  height: 16,
  directions: 4,
  frames: 4,
  frame_speed: 6,
  frame_sequence: [0, 1, 2, 3],
  speed: 1,
  size_x: 13,
  size_y: 15,
  strength: 3,
  health: 150,
  num_moves: 1,
  shot_type: 0,
  shot_pattern: 0,
  shots_allowed: 1,
  solid: 1,
  flying: 0,
  rating: 0,
  type: 0,
  // 'THOR-LTH'
  name: [84, 72, 79, 82, 45, 76, 84, 72, 0],
  func_num: 0,
  func_pass: 0,
  future1: [0, 0, 0, 0, 0, 0],
} as const;

const shot_info = {
  move: 0,
  width: 16,
  height: 16,
  directions: 0,
  frames: 0,
  frame_speed: 0,
  frame_sequence: [0, 0, 0, 0],
  speed: 0,
  size_x: 0,
  size_y: 0,
  strength: 0,
  health: 0,
  num_moves: 0,
  shot_type: 0,
  shot_pattern: 0,
  shots_allowed: 0,
  solid: 0,
  flying: 0,
  rating: 0,
  type: 0,
  // ''
  name: [0, 0, 0, 0, 0, 0, 0, 0, 0],
  func_num: 0,
  func_pass: 0,
  future1: [0, 0, 0, 0, 0, 0],
} as const;

const actor = {
  pic,
  shot,
  actor_info,
  shot_info,
} as const;

export default actor;
