import { BYTE, StructBuffer } from 'struct-buffer';

export type ActorNfo = {
  move: number,
  width: number,
  height: number,
  directions: number,
  frames: number,
  frame_speed: number,
  frame_sequence: number[],
  speed: number,
  size_x: number,
  size_y: number,
  strength: number,
  health: number,
  num_moves: number,
  shot_type: number,
  shot_pattern: number,
  shots_allowed: number,
  solid: number,
  flying: number,
  rating: number,
  type: number,
  name: number[],
  func_num: number,
  func_pass: number,
  future1: number[],
};

export const ActorNfo = new StructBuffer<ActorNfo>(
  'ActorNfo',
  {
    move: BYTE,
    width: BYTE,
    height: BYTE,
    directions: BYTE,
    frames: BYTE,
    frame_speed: BYTE,
    frame_sequence: BYTE[4],
    speed: BYTE,
    size_x: BYTE,
    size_y: BYTE,
    strength: BYTE,
    health: BYTE,
    num_moves: BYTE,
    shot_type: BYTE,
    shot_pattern: BYTE,
    shots_allowed: BYTE,
    solid: BYTE,
    flying: BYTE,
    rating: BYTE,
    type: BYTE,
    name: BYTE[9],
    func_num: BYTE,
    func_pass: BYTE,
    future1: BYTE[6],
  },
);

export type ActorData = {
  pic: number[],
  shot: number[],
  actor_info: ActorNfo,
  shot_info: ActorNfo,
};

export const ActorData = new StructBuffer<ActorData>(
  'ActorData',
  {
    pic: BYTE[16 * 256],
    shot: BYTE[4 * 256],
    actor_info: ActorNfo,
    shot_info: ActorNfo,
  },
);
