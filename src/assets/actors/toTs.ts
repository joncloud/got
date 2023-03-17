import { join } from 'path';
import { ActorData, ActorNfo } from './ActorData';
import { writeFile } from 'fs/promises';
import {
  encodeArray,
  encodeBase64,
  encodeString,
} from '../encode';

export async function toTs(resource: ActorData, name: string, dst: string) {
  let js = '';
  function appendLine(line: string) {
    js += `${line}\n`;
  }
  function appendNfo(nfo: ActorNfo) {
    appendLine(`  move: ${nfo.move},`);
    appendLine(`  width: ${nfo.width},`);
    appendLine(`  height: ${nfo.height},`);
    appendLine(`  directions: ${nfo.directions},`);
    appendLine(`  frames: ${nfo.frames},`);
    appendLine(`  frame_speed: ${nfo.frame_speed},`);
    appendLine(`  frame_sequence: ${encodeArray(nfo.frame_sequence)},`);
    appendLine(`  speed: ${nfo.speed},`);
    appendLine(`  size_x: ${nfo.size_x},`);
    appendLine(`  size_y: ${nfo.size_y},`);
    appendLine(`  strength: ${nfo.strength},`);
    appendLine(`  health: ${nfo.health},`);
    appendLine(`  num_moves: ${nfo.num_moves},`);
    appendLine(`  shot_type: ${nfo.shot_type},`);
    appendLine(`  shot_pattern: ${nfo.shot_pattern},`);
    appendLine(`  shots_allowed: ${nfo.shots_allowed},`);
    appendLine(`  solid: ${nfo.solid},`);
    appendLine(`  flying: ${nfo.flying},`);
    appendLine(`  rating: ${nfo.rating},`);
    appendLine(`  type: ${nfo.type},`);
    // Don't print a string for compatibility with original files.
    // The strings sometimes had garbage data after the \0 in the array.
    appendLine(`  // ${encodeString(nfo.name)}`);
    appendLine(`  name: ${encodeArray(nfo.name)},`);
    appendLine(`  func_num: ${nfo.func_num},`);
    appendLine(`  func_pass: ${nfo.func_pass},`);
    appendLine(`  future1: ${encodeArray(nfo.future1)},`);
  }

  appendLine('\'use strict\';');
  appendLine('');
  appendLine(`const pic = ${encodeBase64(resource.pic)} as const;`);
  appendLine(`const shot = ${encodeBase64(resource.shot)} as const;`);
  appendLine('');
  appendLine('const actor_info = {');
  appendNfo(resource.actor_info);
  appendLine('} as const;');
  appendLine('');
  appendLine('const shot_info = {');
  appendNfo(resource.shot_info);
  appendLine('} as const;');
  appendLine('');
  appendLine('const actor = {');
  appendLine('  pic,');
  appendLine('  shot,');
  appendLine('  actor_info,');
  appendLine('  shot_info,');
  appendLine('} as const;');
  appendLine('');
  appendLine('export default actor;');
  appendLine('');

  const target = join(dst, `${name}.ts`);
  await writeFile(target, js);
  console.log('writing', target);
}
