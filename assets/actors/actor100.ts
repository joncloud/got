const pic = [...Buffer.from('Dw8PDxQUFhoPDw8PDw8PDw8PDxQVFhcZHA8PDw8PDw8PDxQVFhcZGhsdDw8PDw8PDxQVFhcYGRobHB4PDw8PDw8jISIjJCYnKCkqDw8PDw8PIzc3NzckJSYnKg8PDw8PDyM3Nzc3NyQlJioPDw8PDw8jITc3Nzc3JCUqDw8PDw8PDyMhNzc3NyMqDw8PDw8PDw/JIyE3NyMq0g8PDw8PDw/JxdUnIyMq1szSDw8PDw8PzMnT1Soq1trS1g8PDw8PDw/X1tfY2drb2A8PDw8PDw8PzcjJ0tXLzNUPDw8PDw8PD9jU1N3d2NjfDw8PDw8PDw/Y1tbd3dra3w8PDw8PDw8PDw8UFBYaDw8PDw8PDw8PDw8UFRYXGRwPDw8PDw8PDw8UFRYXGRobHQ8PDw8PDw8UFRYXGBkaGxweDw8PDw8PIyEiIyQmJygpKg8PDw8PDyM3Nzc3NyUmJykqDw8PDw8PIyE3Nzc3JCcoKg8PDw8PDw8jITc3NzcmJyoPDw8PDw8PIyE3Nzc3IyoPDw8PDw8PycwmITc3IyoPDw8PDw8PycXU1ScjIyraDw8PDw8PzMXJ09TVKira2Q8PDw8PDw/J19bX19jZ2tgPDw8PDw8PD9jW1tLVy8zVDw8PDw8PDw8PDw/d2NTU3Q8PDw8PDw8PDw8PD93a2t8PDw8PDw8PDw8PFBQWGg8PDw8PDw8PDw8PFBUWFxkcDw8PDw8PDw8PFBUWFxkaGx0PDw8PDw8PFBUWFxgZGhscHg8PDw8PDyMhIiMkJicoKSoPDw8PDw8jNzc3NyQlJicqDw8PDw8PIzc3Nzc3JCUmKg8PDw8PDyMhNzc3NzckJSoPDw8PDw8PIyE3Nzc3IyoPDw8PDw8PD8kjITc3IyrSDw8PDw8PD8nF1ScjIyrWzNIPDw8PDw/MydPVKirW2tLWDw8PDw8PD9fW19jZ2tvYDw8PDw8PDw/NyMnS1cvM1Q8PDw8PDw8P2NTU3d3Y2N8PDw8PDw8PD9jW1t3d2trfDw8PDw8PDw8PDxQUFhoPDw8PDw8PDw8PDxQVFhcZHA8PDw8PDw8PDxQVFhcZGhsdDw8PDw8PDxQVFhcYGRobHB4PDw8PDw8jISIjJCYnKCkqDw8PDw8jITc3NzckJicoKg8PDw8PIyE3Nzc3NyYmKg8PDw8PDyMhNzc3NzclKg8PDw8PDw8PIyE3Nzc3IyoPDw8PDw8PDw8mITc3IyrY0g8PDw8PDw8P1ScjIyra1MzSDw8PDw8PD9PVKira2dbbzNYPDw8PDw/X1tfY2drb2NIPDw8PDw8PzcjJ0tXa2tUPDw8PDw8PD9jU1N3dDw8PDw8PDw8PDw/Y1tbdDw8PDw8PDw8PDw8PDw8UFBYaDw8PDw8PDw8PDw8UFRYXGRwPDw8PDw8PDw8UFRYXGRobHQ8PDw8PDw8UFRYXGBkaGxweDw8PDw8PIyQlyMnKyiUmKg8PDw8PDyM3yR/FxR/KJCoPDw8PDw8jN8jFx8jFyCQqDw8PDw8PIyE3NyMkNzcjKg8PDw8PDw8jITcfHzcjKg8PDw8PDw8PySMhNzcjKtIPDw8PDw8PycXVJyMjKtbM0g8PDw8PzMXJ09UqKtbazszWDw8PDw/J19bX2Nna29jSDw8PDw8PD83IydLVy8zVDw8PDw8PDw/Y1NTd3djY3w8PDw8PDw8P2NbW3d3a2t8PDw8PDw8PDw8PFBQWGg8PDw8PDw8PDw8PFBUWFxkcDw8PDw8PDw8PFBUWFxkaGx0PDw8PDw8PFBUWFxgZGhscHg8PDw8PDyMlyMnKyiQlJioPDw8PDw8jyR/FxR/KNyQqDw8PDw8PI8jFx8jFyDckKg8PDw8PDyM3NyIkNzc3IyoPDw8PDw8PITc3HzcjIyoPDw8PDw8PDyMhNzcjKirSDw8PDw8PD8nNJyMjKtbWzNIPDw8PD8zF29UqKtbOzMzSDw8PDw8PydfW19jZ2tvY1g8PDw8PDw/Y1tbS1cvM1Q8PDw8PDw8PDw8P3d3Y2N8PDw8PDw8PDw8PDw/d2trfDw8PDw8PDw8PDxQUFhoPDw8PDw8PDw8PDxQVFhcZHA8PDw8PDw8PDxQVFhcZGhsdDw8PDw8PDxQVFhcYGRobHB4PDw8PDw8jJCXIycrKJSYqDw8PDw8PIzfJH8XFH8okKg8PDw8PDyM3yMXHyMXIJCoPDw8PDw8jITc3IiQ3NyMqDw8PDw8PDyMhNx8fNyMqDw8PDw8PDw/JIyE3NyMq0g8PDw8PDw/JxdUnIyMq1szSDw8PDw/MxcnT1Soq1trOzNYPDw8PD8nX1tfY2drb2NIPDw8PDw8PzcjJ0tXLzNUPDw8PDw8PD9jU1N3d2NjfDw8PDw8PDw/Y1tbd3dra3w8PDw8PDw8PDw8UFBYaDw8PDw8PDw8PDw8UFRYXGRwPDw8PDw8PDw8UFRYXGRobHQ8PDw8PDw8UFRYXGBkaGxweDw8PDw8PIyQlJsnKysslKg8PDw8PDyMhN8kfxcUfyyoPDw8PDw8jITfIxcfIxckqDw8PDw8PIyE3NzciJDcjKg8PDw8PDw8jISE3Hzc3Kg8PDw8PDw8PySMjITc3IyoPDw8PDw8PycXV1ScjIyrM0g8PDw8PD8nFxcnVKirW28zWDw8PDw/My8zX2Nna29jSDw8PDw8PD83IydLV2trVDw8PDw8PDw/Y1NTd3Q8PDw8PDw8PDw8P2NbW3Q8PDw8PDw8PDw8PDw8PDw8UFxgPDw8PDw8PDw8PDw8VFhgZGg8PDw8PDw8PDw8VFhgZGhscDw8PDw8PDw8UFRcYGRobHB4PDw8PDw8PIyQlJicoKCksDw8PDw8PD8kfxco3IyQlLA8PDw8PD8nHxcXINyEkJSsPDw8PDw8PIiQ3NzchIyUlKw8PDw8PDx8fNyEhISIkJSsPDw8PDw83NyEpKissLCwPDw8PDw8kIiUr2czZ2twPDw8PDw8PKCrJzM3Q2NvdDw8PDw8PDw/X1tfY2dna3w8PDw8PDw8PD83IycvV3w8PDw8PDw8PDw/Y1tfZ3w8PDw8PDw8PDw/Y1tfZ2t8PDw8PDw8PDw8PDw8PFBcYDw8PDw8PDw8PDw8PFRYYGRoPDw8PDw8PDw8PFRYXGBobHA8PDw8PDw8PFBUWFxkaGxweDw8PDw8PDyMkJicnKCgpLA8PDw8PDw8Pxx/KNyMkKCksDw8PDw8Px8XFyMohIyUoKSwPDw8PDyIkNzchISIkJSksDw8PDw8fHzchISwsLCwsDw8PDw8PNzchLCza290PDw8PDw8PJCIkK9nazNrdDw8PDw8PDygqLNzJzM3Q3Q8PDw8PDw8P19bX2NnZ2t8PDw8PDw8PzcjM0d/fzczN3w8PDw8P2NbX2d8PD9nW19nfDw8P2NbX2d8PD9jX2Nna3w8PDw8PDw8PDxQXGA8PDw8PDw8PDw8PDxUWGBkaDw8PDw8PDw8PDxUWGBkaGxwPDw8PDw8PDxQVFxgZGhscHg8PDw8PDw8jJCUmJygoKSwsDw8PDw8PyR/FyiIjJigpKisPDw8PycfFxcg3ISQmKCkrDw8PDw8iJDc3NyEjJCYrDw8PDw8PHx83ISEhIisrDw8PDw8PDzc3ISkqKyzcDw8PDw8PDyQiJSvZzNna3A8PDw8PDw8oKsnMzdDY290PDw8PDw8PD9fW19jZ2drfDw8PDw8PDw8PzcjJy9XfDw8PDw8PDw8PD9jW19nfDw8PDw8PDw8PD9jW19na3w8PDw8PDw8PDw8PDw8UFxgPDw8PDw8PDw8PDw8VFhgZGg8PDw8PDw8PDw8VFhgZGhscDw8PDw8PDw8UFRcYGRobHB4PDw8PDw8PIyQmJycoKCksDw8PDw8PDx/IyjciIyQoKSwPDw8PDw/HxSI3NyEjJSgpLA8PDw8PIiQ3NyEhIiQlKSwPDw8PDx83NyEhKiwsLCwPDw8PDw83NyEqKtrb3Q8PDw8PDw8kIiQqzNrZ2t0PDw8PDw8PKMnMzdDa2NvdDw8PDw8PDw/X1tfY2dna3w8PDw8PDw/NyMzR39/NzM3fDw8PDw/Y1tfZ3w8P2dbX2d8PDw/Y1tfZ3w8P2NfY2drfDw8PDw8PDw8UFxgPDw8PDw8PDw8PDw8VFhgZGg8PDw8PDw8PDw8VFhgZGhscDw8PDw8PDw8UFRcYGRobHB4PDw8PDw8PIyUmJygoKSwsDw8PDw8PDyMiIyQlyckfyw8PDw8PDw8jNyElJMXHyMrLDw8PDw8jITc3ISIiIyQlDw8PDw8PIyE3Nzc3ISIfHw8PDw8PDw8pKissLCwjIicPDw8PDw8PD9na3M/ZLCQlKQ8PDw8PDw/Y293KzM3QLCsPDw8PDw8P19bX2NnZ2t8PDw8PDw8PDw/b1c3IycsPDw8PDw8PDw8PD9rZ19bYDw8PDw8PDw8PDw/a2NbX2doPDw8PDw8PDw8PFBcYDw8PDw8PDw8PDw8PFRYYGRoPDw8PDw8PDw8PFRYXGBobHA8PDw8PDw8PFBUWFxkaGxweDw8PDw8PDyMlJicoKCksLA8PDw8PDyMhNyIjJMofyQ8PDw8PDyMhNzc3IcrHxcfKDw8PDw8jITc3Nzc3NyIjJQ8PDw8PDycpKywsJSEhHx8PDw8PDw8PD9zb2iwsJSEnDw8PDw8PDw/Z2s/a2S0lJSkPDw8PDw8P2MrMzdDcLCwrDw8PDw8PD9fW19jZ2drfDw8PDw8PD83Iycvf383MzdIPDw8PD9vZ19bfDw/f2dbX2A8PDw/b2NbX2d8PD9/Z1tfYDw8PDw8PDxQXGA8PDw8PDw8PDw8PDxUWGBkaDw8PDw8PDw8PDxUWGBkaGxwPDw8PDw8PDxQVFxgZGhscHg8PDw8PDyMjJSYnKCgpLCwPDw8PDyMhISIjJCXJyR/LDw8PDw8jITc3ISUkxcfIyssPDw8PDychNzc3IiIjJCUPDw8PDw8PJychNzchIh8fDw8PDw8PDw/cKywsLCMiJw8PDw8PDw8P2drcz9ktLCUpDw8PDw8PD9jb3crMzdDeLA8PDw8PDw/X1tfY2dna3w8PDw8PDw8PD9vVzcjJyw8PDw8PDw8PDw8P2tnX1tgPDw8PDw8PDw8PD9rY1tfZ2g8PDw8PDw8PDw8UFxgPDw8PDw8PDw8PDw8VFhgZGg8PDw8PDw8PDw8VFhgZGhscDw8PDw8PDw8UFRcYGRobHB4PDw8PDw8PIyUmJygoKSwsDw8PDw8PIyE3IiMkJcrJHw8PDw8PIyE3NzchIiMix8oPDw8PDyMhNzc3Nzc3IiMlDw8PDw8PJykrLCwlISEhHw8PDw8PDw8P3N3eLCwlIicPDw8PDw8PD9na3N7PLSUkKQ8PDw8PDw/Y293eyszN0CsPDw8PDw8P19bX2NnZ2t8PDw8PDw8PzcjJy9/fzczN0g8PDw8P29nX1t8PD9/Z1tfYDw8PD9vY1tfZ3w8P39nW19gPDw==', 'base64')] as const;
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
