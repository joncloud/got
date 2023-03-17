'use strict';

const pic = [...Buffer.from('Dw8PFg8PDw8PDw8WDw8PDw8PDw8XDw8PDw8XDw8PDw8WDw8PGA8PDw8PGA8PDxYPDxcPDxkPHQ8dDxkPDxcPDw8PGA8PGhwMHBoPDxgPDw8PDw8ZGhxHHkccGhkPDw8PDw8PDw8eFxMRHg8PDw8PDw8PGBkbHx0eHR8bGRgPDw8WFw8PHxwUJhIcHw8PFxYPDw8PHxwmJBQiIBsfDw8PDw8PHA8bFxYjEhEZDxwPDw8PDxoPDxomEyIYDw8aDw8PDw8ZDw8ZEyQRFw8PGQ8PDw8PGA8PDxgXFg8PDxgPDw8PDw8YDw8PDw8PDxgPDw8PDw8PFg8PDw8PDw8WDw8PDw8PDw8PDxYPFg8PDw8PDw8PDw8PDxcPDw8XDw8PDw8PDw8WDw8YDw8PGA8PFg8PDw8PFw8ZDx0PHQ8ZDxcPDw8PDw8YDxocDBwaDxgPDw8PFhcPGRocRx5HHBoZDxcWDw8PGA8PHhcTER4PDxgPDw8PDw8ZGx8dHh0fGxkPDw8PDw8PDx8cFCYSHB8PDw8PDw8PDx8cJiQUIiAbHw8PDw8PDxwPGxcWIxIRGQ8cDw8PDxoPDw8aJhMiGA8PDxoPDw8ZDw8PGRMkERcPDw8ZDw8PGA8PDw8YFxYPDw8PGA8PGA8PDw8PDw8PDw8PDw8YDxYPDw8PDw8PDw8PDw8PFg8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8WDw8PDw8PDxYPDw8PDw8PGA8PDw8PDw8YDw8PDw8PGA8PDxYXGA8PDxgPDw8PDxkPDxcRJBMZDw8ZDw8PDw8aDw8YIhMmGg8PGg8PDw8PHA8ZERIjFhcbDxwPDw8PDw8fGyAiFCQmHB8PDw8PFhcPDx8cEiYUHB8PDxcWDw8PGBkbHx0eHR8bGRgPDw8PDw8PDx4RExceDw8PDw8PDw8PGRocRx5HHBoZDw8PDw8PGA8PGhwMHBoPDxgPDw8PFw8PGQ8dDx0PGQ8PFw8PFg8PDxgPDw8PDxgPDw8WDw8PDw8XDw8PDw8XDw8PDw8PDw8WDw8PDw8PDxYPDw8PFg8PDw8PDw8PDw8PDw8WDxgPDw8PDw8PDw8PDw8PGA8PGA8PDw8WFxgPDw8PGA8PDxkPDw8XESQTGQ8PDxkPDw8aDw8PGCITJhoPDw8aDw8PDxwPGRESIxYXGw8cDw8PDw8PHxsgIhQkJhwfDw8PDw8PDw8fHBImFBwfDw8PDw8PDw8ZGx8dHh0fGxkPDw8PDw8YDw8eERMXHg8PGA8PDxYXDxkaHEceRxwaGQ8XFg8PDw8YDxocDBwaDxgPDw8PDw8XDxkPHQ8dDxkPFw8PDw8PFg8PGA8PDxgPDxYPDw8PDw8PDxcPDw8XDw8PDw8PDw8PDw8PFg8WDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw==', 'base64')] as const;
const shot = [...Buffer.from('AAAAAAAAAAAAAAAAAAAAAAAAHycdCAAAAAAAAAAAAAAAHylHDCkIAAAAAAAAAAAAACk5R0c5HwAAAAAAAAAAAAAfKTlHKR8AAAAAAAAAAAAAAB8iGx8AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAGx8fAAAAAAAAAAAAAAAAHyUmOR8AAAAAAAAAAAAAHyZAQ0M5KQAAAAAAAAAAABsmR0BARzkfAAAAAAAAAAAAHyZGRkA2HwAAAAAAAAAAAAAdGR8fGwAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAfJx0IAAAAAAAAAAAAAAAfKQxHKQgAAAAAAAAAAAAAKTlHRzkfAAAAAAAAAAAAAB8pRzkpHwAAAAAAAAAAAAAAHyIbHwAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHx8bAAAAAAAAAAAAAAAAHyYmJR8AAAAAAAAAAAAAKSZDQ0A5HwAAAAAAAAAAHyZHQEBHJhsAAAAAAAAAAB82QEZGOR8AAAAAAAAAAAAAGx8fGR0AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA==', 'base64')] as const;

const actor_info = {
  move: 10,
  width: 16,
  height: 16,
  directions: 2,
  frames: 2,
  frame_speed: 8,
  frame_sequence: [0, 1, 0, 1],
  speed: 1,
  size_x: 15,
  size_y: 15,
  strength: 255,
  health: 20,
  num_moves: 1,
  shot_type: 0,
  shot_pattern: 1,
  shots_allowed: 1,
  solid: 2,
  flying: 0,
  rating: 10,
  type: 2,
  // 'SPIDER'
  name: [83, 80, 73, 68, 69, 82, 0, 0, 0],
  func_num: 0,
  func_pass: 0,
  future1: [0, 0, 0, 0, 0, 0],
} as const;

const shot_info = {
  move: 1,
  width: 16,
  height: 16,
  directions: 1,
  frames: 4,
  frame_speed: 6,
  frame_sequence: [0, 1, 2, 3],
  speed: 1,
  size_x: 7,
  size_y: 5,
  strength: 255,
  health: 10,
  num_moves: 4,
  shot_type: 0,
  shot_pattern: 0,
  shots_allowed: 0,
  solid: 1,
  flying: 1,
  rating: 0,
  type: 3,
  // 'SPIDERSH'
  name: [83, 80, 73, 68, 69, 82, 83, 72, 0],
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

