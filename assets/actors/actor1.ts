'use strict';

const pic = [...Buffer.from('AAAAAAAAAFBQUAAAAAAAAAAAAAAAAFBVVldVAAAAAAAAAAAAAFBVERARV1UAAAAAAAAAAABQExDwEBZVAAAAAAAAAAAAUFUREBFXVQAAAAAAAAAAUFFSVVZXVFUAAAAAAAAAAFBRUlNTVFUAAAAAAAAAAABQUVJTU1RVAAAAAAAAAAAAUFFSU1RVAAAAAAAAAAAAUFFSU1NUVQAAAAAAAAAAAFBRUlNUVQAAAAAAAAAAAABQUVJTVFUAAAAAAAAAAAAA0lBRUlNUVQAAAAAAANDU1NJQUVJTU1TS0tLZAAAA0NDQ0lBRUlRU0tnZAAAAAAAAANDU1NTZ2dkAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABQUFMAAAAAAAAAAAAAAABQUFBUVQAAAAAAAAAAAABQVVVWV1dVAAAAAAAAAAAAUBMQ8BAWVQAAAAAAAAAAAFBVERARV1UAAAAAAAAAAABQUVVWV1RVAAAAAAAAAAAAUFFSU1NUVQAAAAAAAAAAAFBRUlNTVFUAAAAAAAAAAABQUVJTVFUAAAAAAAAAAAAAUFFSU1RVAAAAAAAAAAAAANJQUVJTVFUAAAAAAADQ1NTSUFFSU1NU0tLS2QAAANDQ0NJQUVJUVNLZ2QAAAAAAAADQ1NTU2dnZAAAAAAAAAABQUFMAAAAAAAAAAAAAAABQUFBUVQAAAAAAAAAAAABQUFBQU1RVAAAAAAAAAAAAVVRUVVZXVwAAAAAAAAAAAFBVVVZXV1UAAAAAAAAAAABQUVNTU1RVAAAAAAAAAAAAUFFSU1NUVQAAAAAAAAAAAFBRUlNTVFUAAAAAAAAAAAAAUFFRUlRVAAAAAAAAAAAAAFBRUVJTVFUAAAAAAAAAAAAAUFFSU1RVAAAAAAAAAAAAAFBRUlNUVQAAAAAAAAAAAADSUFFSU1RVAAAAAAAA0NTU0lBRUlNTVNLS0tkAAADQ0NDSUFFSVFTS2dkAAAAAAAAA0NTU1NnZ2QAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAFBQUAAAAAAAAAAAAAAAAFBQUFBVAAAAAAAAAAAAAFBVVVZXV1UAAAAAAAAAAABQExDwEBZVAAAAAAAAAAAAUFUREBFXVQAAAAAAAAAAAFBRVVZXVFUAAAAAAAAAAABQUVJTU1RVAAAAAAAAAAAAUFFSU1NUVQAAAAAAAAAAAFBRUlNUVQAAAAAAAAAAAABQUVJTVFUAAAAAAAAAAAAA0lBRUlNUVQAAAAAAANDU1NJQUVJTU1TS0tLZAAAA0NDQ0lBSUlRU0tnZAAAAAAAAANDU1NTZ2dkAAAAAAAAAAAAAAABQUFAAAAAAAAAAAAAAAABQVVZXVQAAAAAAAAAAAABQVREQEVdVAAAAAAAAAAAAUBMQ8BAWVQAAAAAAAAAAAFBVERARV1UAAAAAAAAAAFBRUlVWV1RVAAAAAAAAAABQUVJTU1RVAAAAAAAAAAAAUFFSU1NUVQAAAAAAAAAAAFBRUlNUVQAAAAAAAAAAAFBRUlNTVFUAAAAAAAAAAABQUVJTVFUAAAAAAAAAAAAAUFFSU1RVAAAAAAAAAAAAANJQUVJTVFUAAAAAAADS0tLSUFFSU1NU0tLS0gAAANLS0tJQUVJUVNLS0gAAAAAAAADS0tLS0tLSAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAUFBTAAAAAAAAAAAAAAAAUFBQVFUAAAAAAAAAAAAAUFVVVldXVQAAAAAAAAAAAFATEPAQFlUAAAAAAAAAAABQVREQEVdVAAAAAAAAAAAAUFFVVldUVQAAAAAAAAAAAFBRUlNTVFUAAAAAAAAAAABQUVJTU1RVAAAAAAAAAAAAUFFSU1RVAAAAAAAAAAAAAFBRUlNUVQAAAAAAAAAAAADSUFFSU1RVAAAAAAAA0tLS0lBRUlNTVNLS0tIAAADS0tLSUFFSVFTS0tIAAAAAAAAA0tLS0tLS0gAAAAAAAAAAUFBTAAAAAAAAAAAAAAAAUFBQVFUAAAAAAAAAAAAAUFBQUFNUVQAAAAAAAAAAAFVUVFVWV1cAAAAAAAAAAABQVVVWV1dVAAAAAAAAAAAAUFFTU1NUVQAAAAAAAAAAAFBRUlNTVFUAAAAAAAAAAABQUVJTU1RVAAAAAAAAAAAAAFBRUVJUVQAAAAAAAAAAAABQUVFSU1RVAAAAAAAAAAAAAFBRUlNUVQAAAAAAAAAAAABQUVJTVFUAAAAAAAAAAAAA0lBRUlNUVQAAAAAAANLS0tJQUVJTU1TS0tLSAAAA0tLS0lBRUlRU0tLSAAAAAAAAANLS0tLS0tIAAAAAAAAAAAAAAAAA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', 'base64')] as const;
const shot = [...Buffer.from('AAAAAAAAAAAAAAAAAAAAAAAAAAAiAAAAAAAAAAAiAAAAAAAAACIAAAAAAAAiAAAAAAAAAAAiAAAAAAAAIgAAAAAAAAAAACcAAAAAJwAAAAAAAAAAAAAAJwAAJwAAAAAAAAAAAAAAAEpKSgAAACIAAAAAAAAAAEpKR0pKACcAIgAAAAAiJydKR0dHSicAAAAiAAAiAAAASkpHSkoAAAAAAAAiAAAAAABKSkonAAAAAAAAAAAAAAAAJwAAACcAAAAAAAAAAAAAJwAAAAAAIgAAAAAAAAAAIgAAAAAAACIAAAAAAAAiIgAAAAAAAAAiAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAACIAAAAAAAAAAAAAAAAAAAAAIgAAAAAAAAAAAAAiAAAAAAAiAAAAAAAAAAAAIgAAAAAAJwAAAAAAACIAAAAiAAAAACcAAAAAIiIAAAAAACcAAEpKSgAAJwAAAAAAAAAAJ0pKR0pKJwAAAAAAAAAAAABKR0dHSgAAAAAAAAAAAAAASkpHSkoAAAAAAAAAAAAAACdKSkoAJwAAAAAAAAAAACcAACcAAAAnAAAAAAAiIiIAAAAAJwAAACIiAAAAAAAAAAAAAAAiAAAAACIAAAAAAAAAAAAiAAAAAAAAAAAAAAAAAAAiAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAIgAAAAAAAAAiIgAAAAAAACIAAAAAAAAiAAAAAAAAAAAiAAAAAAAnAAAAAAAAAAAAACcAAAAnAAAAAAAAAAAAAAAAJ0pKSgAAAAAAIgAAAAAAAEpKR0pKAAAAIgAAIgAAACdKR0dHSicnIgAAAAAiACcASkpHSkoAAAAAAAAAACIAAABKSkoAAAAAAAAAAAAAAAAnAAAnAAAAAAAAAAAAAAAnAAAAACcAAAAAAAAAAAAiAAAAAAAAIgAAAAAAAAAAIgAAAAAAACIAAAAAAAAAIgAAAAAAAAAAIgAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAiAAAAAAAAAAAAAAAAAAAiAAAAAAAAAAAAIgAAAAAiAAAAAAAAAAAAAAAiIgAAACcAAAAAIiIiAAAAAAAnAAAAJwAAJwAAAAAAAAAAACcASkpKJwAAAAAAAAAAAAAASkpHSkoAAAAAAAAAAAAAAEpHR0dKAAAAAAAAAAAAACdKSkdKSicAAAAAAAAAACcAAEpKSgAAJwAAAAAAIiIAAAAAJwAAAAAiAAAAIgAAAAAAACcAAAAAACIAAAAAAAAAAAAiAAAAAAAiAAAAAAAAAAAAACIAAAAAAAAAAAAAAAAAAAAAIgAAAAAAAAAAAAAAAAAAAAAAAAAAAA==', 'base64')] as const;

const actor_info = {
  move: 1,
  width: 16,
  height: 16,
  directions: 1,
  frames: 4,
  frame_speed: 6,
  frame_sequence: [0, 1, 2, 3],
  speed: 2,
  size_x: 15,
  size_y: 15,
  strength: 0,
  health: 255,
  num_moves: 1,
  shot_type: 100,
  shot_pattern: 2,
  shots_allowed: 3,
  solid: 2,
  flying: 0,
  rating: 10,
  type: 2,
  // 'WORMY'
  name: [87, 79, 82, 77, 89, 0, 0, 109, 109],
  func_num: 0,
  func_pass: 0,
  future1: [255, 0, 0, 0, 0, 0],
} as const;

const shot_info = {
  move: 1,
  width: 16,
  height: 16,
  directions: 1,
  frames: 4,
  frame_speed: 4,
  frame_sequence: [0, 1, 2, 3],
  speed: 1,
  size_x: 15,
  size_y: 15,
  strength: 255,
  health: 0,
  num_moves: 8,
  shot_type: 0,
  shot_pattern: 0,
  shots_allowed: 0,
  solid: 1,
  flying: 1,
  rating: 0,
  type: 3,
  // 'WORMSPIT'
  name: [87, 79, 82, 77, 83, 80, 73, 84, 0],
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

