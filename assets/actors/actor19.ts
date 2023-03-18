const pic = [...Buffer.from('AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAbFhMaGAAAAAAAAAAAABsaFBQTGhQWGAAAAAAAABwXGhUUFBQaFRYZAAAAABoZFxYaFRQVGxYWGBgAABwbGRcWGxUVFRwWFxgaHgAaHhkXFxwWFhYdFxcaGRsAHBoaGxwdHhcXFx4YGxobABwbGhkZHBsdHRgbHB0aHAAdHBsaHBkYGhweGRoaHBwAAB0cGhsZHRkdGRsaHBoAAAAAGhwbGxwbHBsbHBwAAAAAAAAdHRocGxwaHR0AAAAAAAAAAAAdHR0dGgAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAGhcYGBsAAAAAAAAAAAAZGBsVFRYcGBkAAAAAAAAaGBYcFBMUHRYYGgAAAAAaGhscHR4TFBQeFhsaAAAbGhgXFhwbHR0VGxwdGhsAHBkZFxwVFRocHhYXGRwcABwaGRoXFh0WHRYXGBkaHAAcGhoYGBccFhwXGBgaGhwAHRsaGhkcFxgYHBgaGxwcAAAcHBsaGRkZGRoaGxwcAAAAAB0cGxoaGhoaGxwdAAAAAAAAHR0bHBscGx0dAAAAAAAAAAAAHR0dHR0AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABwZGRodAAAAAAAAAAAAGxwdHhcXGB4bAAAAAAAAGhgXHBsdHRYbHB0AAAAAGxkXHBUUGhweFxgaHAAAHBoZGxYUHRMdFBYXGRodABwaGxcWFRwUHBUWFxkbHAAcGhwXFxoVFBUaFhcZGh0AHBsZGBcWFhYVGhcYGRsdAB0bGxkZFxcWFxcbGRsbHQAAHRsaGRkYGBgZGRwcHQAAAAAdGxsZGhkaGRsbHQAAAAAAAB0cGxsbGxsdHQAAAAAAAAAAAB0dHR0dAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAYFxgYGQAAAAAAAAAAABkYGBUVFhsYGQAAAAAAABobFhUUExoVFhgaAAAAABoYFhoUFBMaFBYWGBoAABsaGBcaFRQUFBoVFxgaGwAcGRkXFxoVFRYbFhcZGRwAHBoZGBcbFhYWHBcYGRoeABoeGhgYHBcWFx0YGBoaHAAdGxobHB0eGBgZHhobHBwAABwcGxocGx0dGRscHRwAAAAAHRwcGhoaHB4bHB0AAAAAAAAaHRsdGx0bHR0AAAAAAAAAAAAdHB0cHQAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAGxYTGhgAAAAAAAAAAAAbGhQUExoUFhgAAAAAAAAcFxoVFBQUGhUWGQAAAAAaGRcWGhUUFRsWFhgYAAAcGxkXFhsVFRUcFhcYGh4AGh4ZFxccFhYWHRcXGhkbABwaGhscHR4XFxceGBsaGwAcGxoZGRwbHR0YGxwdGhwAHRwbGhwZGBocHhkaGhwcAAAdHBobGR0ZHRkbGhwaAAAAABocGxscGxwbGxwcAAAAAAAAHR0aHBscGh0dAAAAAAAAAAAAHR0dHRoAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABgXGBgZAAAAAAAAAAAAGRgYFRUWGxgZAAAAAAAAGhsWFRQTGhUWGBoAAAAAGhgWGhQUExoUFhYYGgAAGxoYFxoVFBQUGhUXGBobABwZGRcXGhUVFhsWFxkZHAAcGhkYFxsWFhYcFxgZGh4AGh4aGBgcFxYXHRgYGhocAB0bGhscHR4YGBkeGhscHAAAHBwbGhwbHR0ZGxwdHAAAAAAdHBwaGhocHhscHQAAAAAAABodGx0bHRsdHQAAAAAAAAAAAB0cHRwdAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAcGRkaHQAAAAAAAAAAABscHR4XFxgeGwAAAAAAABoYFxwbHR0WGxwdAAAAABsZFxwVFBocHhcYGhwAABwaGRsWFB0THRQWFxkaHQAcGhsXFhUcFBwVFhcZGxwAHBocFxcaFRQVGhYXGRodABwbGRgXFhYWFRoXGBkbHQAdGxsZGRcXFhcXGxkbGx0AAB0bGhkZGBgYGRkcHB0AAAAAHRsbGRoZGhkbGx0AAAAAAAAdHBsbGxsbHR0AAAAAAAAAAAAdHR0dHQAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAGhcYGBsAAAAAAAAAAAAZGBsVFRYcGBkAAAAAAAAaGBYcFBMUHRYYGgAAAAAaGhscHR4TFBQeFhsaAAAbGhgXFhwbHR0VGxwdGhsAHBkZFxwVFRocHhYXGRwcABwaGRoXFh0WHRYXGBkaHAAcGhoYGBccFhwXGBgaGhwAHRsaGhkcFxgYHBgaGxwcAAAcHBsaGRkZGRoaGxwcAAAAAB0cGxoaGhoaGxwdAAAAAAAAHR0bHBscGx0dAAAAAAAAAAAAHR0dHR0AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABsWExoYAAAAAAAAAAAAGxoUFBMaFBYYAAAAAAAAHBcaFRQUFBoVFhkAAAAAGhkXFhoVFBUbFhYYGAAAHBsZFxYbFRUVHBYXGBoeABoeGRcXHBYWFh0XFxoZGwAcGhobHB0eFxcXHhgbGhsAHBsaGRkcGx0dGBscHRocAB0cGxocGRgaHB4ZGhocHAAAHRwaGxkdGR0ZGxocGgAAAAAbHBsbHBscGhscHAAAAAAAAB0dGhwbHBsdHQAAAAAAAAAAAB0dHR0cAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAaFhYYHBoAAAAAAAAAABMTFBobHRgZGgAAAAAAABUTFBQVFRwXGBkbAAAAABcVFBQUFB4bFxcZGRsAABsYFhobHB0VFx4YGBoaHAAcGhoWFRUWFh0cHRwaGxwAHRgYFhYWFxYdGhkZGhsdABsZGBgXFxceGxgdHBsbHAAdGhoYGhscHRwZGhoaHB0AABwaGhkZGRwZHBobHB0AAAAAHBobGhobGxsaHB0AAAAAAAAcHBsbGhscHBoAAAAAAAAAAAAcHhwdHAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAGhkZGRsAAAAAAAAAAAAWFxoYGBkaGxsAAAAAAAAVFRUWHBgcGRobGgAAAAAaFBQVFR0XHRgaGhwcAAATHBQUFR4cGhcYHBobHB0AFRMdHBsVHR0bHBkZGxsdABYVGxUeFhYXHh0cGxocHQAaFRoVFh0XFxgcGRobHhoAHhoXFhYcFxgYGxobGxwdAAAbGRcYGxgYGRobGxwcAAAAABoaGBoYGRoaGhwcAAAAAAAAHBoaGhobGxocAAAAAAAAAAAAHBobGxwAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABUWGhgZAAAAAAAAAAAAExoUFRsWGBkaAAAAAAAAFRMUHBUcFhcYGhoAAAAAFxoUFBQcHRwbGhkZGwAAGxgWHB0UGx4XFxgYGhocABwYFhYVGh0WFxcYGRobHAAbGBgcHRwdFhgYGRkaGh0AGxoaGBceFxgdHBsaGxscAB0aGhgYFxseGRkaGhwcHQAAHBsaGRkcGRkaGhscHQAAAAAcGhsaHRsaGxwcHQAAAAAAABwaHBsbGxocHQAAAAAAAAAAABwdHB0eAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAbFhMaGAAAAAAAAAAAABsaFBQTGhQWGAAAAAAAABwXGhUUFBQaFRYZAAAAABoZFxYaFRQVGxYWGBgAABwbGRcWGxUVFRwWFxgaHgAaHhkXFxwWFhYdFxcaGRsAHBoaGxwdHhcXFx4YGxobABwbGhkZHBsdHRgbHB0aHAAdHBsaHBkYGhweGRoaHBwAAB0cGhsZHRkdGRsaHBoAAAAAGxwbGxwbHBobHBwAAAAAAAAdHRocGxwbHR0AAAAAAAAAAAAdHR0dHAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAFRYaGBkAAAAAAAAAAAATGhQVGxYYGRoAAAAAAAAVExQcFRwWFxgaGgAAAAAXGhQUFBwdHBsaGRkbAAAbGBYcHRQbHhcXGBgaGhwAHBgWFhUaHRYXFxgZGhscABsYGBwdHB0WGBgZGRoaHQAbGhoYFx4XGB0cGxobGxwAHRoaGBgXGx4ZGRoaHBwdAAAcGxoZGRwZGRoaGxwdAAAAABwaGxodGxobHBwdAAAAAAAAHBocGxsbGhwdAAAAAAAAAAAAHB0cHR4AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABoZGRkbAAAAAAAAAAAAFhcaGBgZGhsbAAAAAAAAFRUVFhwYHBkaGxoAAAAAGhQUFRUdFx0YGhocHAAAExwUFBUeHBoXGBwaGxwdABUTHRwbFR0dGxwZGRsbHQAWFRsVHhYWFx4dHBsaHB0AGhUaFRYdFxcYHBkaGx4aAB4aFxYWHBcYGBsaGxscHQAAGxkXGBsYGBkaGxscHAAAAAAaGhgaGBkaGhocHAAAAAAAABwaGhoaGxsaHAAAAAAAAAAAABwaGxscAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAaFhYYHBoAAAAAAAAAABMTFBobHRgZGgAAAAAAABUTFBQVFRwXGBkbAAAAABcVFBQUFB4bFxcZGRsAABsYFhobHB0VFx4YGBoaHAAcGhoWFRUWFh0cHRwaGxwAHRgYFhYWFxYdGhkZGhsdABsZGBgXFxceGxgdHBsbHAAdGhoYGhscHRwZGhoaHB0AABwaGhkZGRwZHBobHB0AAAAAHBobGhobGxsaHB0AAAAAAAAcHBsbGhscHBoAAAAAAAAAAAAcHhwdHAAAAAAAAAAAAAAAAAAAAAAAAAAAAA==', 'base64')] as const;
const shot = [...Buffer.from('AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA==', 'base64')] as const;

const actor_info = {
  move: 15,
  width: 16,
  height: 16,
  directions: 4,
  frames: 4,
  frame_speed: 2,
  frame_sequence: [0, 1, 2, 3],
  speed: 2,
  size_x: 15,
  size_y: 15,
  strength: 0,
  health: 255,
  num_moves: 1,
  shot_type: 0,
  shot_pattern: 0,
  shots_allowed: 0,
  solid: 2,
  flying: 0,
  rating: 10,
  type: 2,
  // 'BOULDER'
  name: [66, 79, 85, 76, 68, 69, 82, 0, 0],
  func_num: 5,
  func_pass: 1,
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
