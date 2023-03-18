const pic = [...Buffer.from('Dw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8POA8PDw8PDw8PDw8PDw8PEDoTDw8PDw8PDw8PDw8PDxIRFA8PDw8PDw8PDw8PDw/XEtsPDw8PDw8PDw8PDw/Y29zd3A8PDw8PDw/R09TW29za3dvW1NPRDw/R1dvc3Nzc293c3Nzb1dEP0tbX2Nna29zd29nY19bSDw/Y2drb3N0Y39zb2tnYDw8PDw8PDw8SFBUPDw8PDw8PDw8PDw8REBUREw8PDw8PDw8PDw8PEhAXERIPDw8PDw8PDw8PDw8TDxMPDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDzgPDw8PDw8PDw8PDw8PDxA6Ew8PDw8PDw8PDw8PDw8SERQPDw8PDw8PDw8PDw8P1xLbDw8PDw8PDw8PDw8P2Nvc3dwPDw8PDw8PD9HT1tvc2t3b1tPRDw8PD9HV29zc3Nvd3Nzb1dEPDw/S1tfZ2tvc3dvZ19bSDw8PD9jZ29zdGN/c29nYDw8PDw8PDw8PEhQVDw8PDw8PDw8PDw8PERAVERMPDw8PDw8PDw8PDxIQFxESDw8PDw8PDw8PDw8PEw8TDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8POA8PDw8PDw8PDw8PDw8PEDoTDw8PDw8PDw8PDw8PDxIRFA8PDw8PDw8PDw8PD9jb3N3cDw8PDw8PDw8PD9Pb3Nrd29MPDw8PDw8PD9Xb3Nzb3dzb1Q8PDw8PDw/W19rb3N3b19YPDw8PDw8PD9nc3Rjf3NkPDw8PDw8PDw8PDxIUFQ8PDw8PDw8PDw8PDxEQFRETDw8PDw8PDw8PDw8SEBcREg8PDw8PDw8PDw8PDxMPEw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8POA8PDw8PDw8PDw8PDw8PEDoTDw8PDw8PDw8PDw8PDxIRFA8PDw8PDw8PDw8PDw/XEtsPDw8PDw8PDw8PDw/Y29zd3A8PDw8PDw8P0dPW29za3dvW09EPDw8P0dXb3Nzc293c3NvV0Q8PD9LW19na29zd29nX1tIPDw8P2Nnb3N0Y39zb2dgPDw8PDw8PDw8SFBUPDw8PDw8PDw8PDw8REBUREw8PDw8PDw8PDw8PEhAXERIPDw8PDw8PDw8PDw8TDxMPDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PEw8TDw8PDw8PDw8PDw8PEhAXERIPDw8PDw8PDw8PDxEQFRETDw8PDw8PDw8PDw8PEhQVDw8PDw8PDw/R09TW3NsY3dzW1NPRDw/R1tfY2drb2tzb2djX1tEP0tXb3Nzc3Nvc3Nzc29XSDw/Y2drb29zc3Nvb2tnYDw8PDw8PD9fb3t3cDw8PDw8PDw8PDw8P2RLbDw8PDw8PDw8PDw8PDxIRFA8PDw8PDw8PDw8PDw8QOhMPDw8PDw8PDw8PDw8PDzkPDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDxMPEw8PDw8PDw8PDw8PDxIQFxESDw8PDw8PDw8PDw8REBUREw8PDw8PDw8PDw8PDxIUFQ8PDw8PDw8PD9HU1tzbGN3c1tPRDw8PD9HW2Nna29rc29nX1tEPDw/S1dzc3Nzb3Nzc29XSDw8PD9ja29vc3Nzb29nYDw8PDw8PDw/X297d3A8PDw8PDw8PDw8PD9kS2w8PDw8PDw8PDw8PDw8SERQPDw8PDw8PDw8PDw8PEDoTDw8PDw8PDw8PDw8PDw85Dw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8TDxMPDw8PDw8PDw8PDw8SEBcREg8PDw8PDw8PDw8PERAVERMPDw8PDw8PDw8PDw8SFBUPDw8PDw8PDw8PD9Hc2xjd3NEPDw8PDw8PD9HW2tva3NvW0Q8PDw8PDw/S1dzc29zc1dIPDw8PDw8PD9jb3Nzc29gPDw8PDw8PDw8P19ve3dwPDw8PDw8PDw8PDw8SERQPDw8PDw8PDw8PDw8PEDoTDw8PDw8PDw8PDw8PDw85Dw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PEw8TDw8PDw8PDw8PDw8PEhAXERIPDw8PDw8PDw8PDxEQFRETDw8PDw8PDw8PDw8PEhQVDw8PDw8PDw8P0dTW3NsY3dzW09EPDw8P0dbY2drb2tzb2dfW0Q8PD9LV3Nzc3Nvc3Nzb1dIPDw8P2Nrb29zc3Nvb2dgPDw8PDw8PD9fb3t3cDw8PDw8PDw8PDw8P2RLbDw8PDw8PDw8PDw8PDxIRFA8PDw8PDw8PDw8PDw8QOhMPDw8PDw8PDw8PDw8PDzkPDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PD9HSDw8PDw8PDw8PDw8PD9HV1tgPDw8PDw8PDw8PDw/T29fZDw8PDw8PDw8PDw8P1NzY2g8PDw8PDw8PDw8PD9bc2dsPDw8PDw8PDw8PD9jb3NrcDxESDw8PDw8QEtfb3Nzb2xIQEBMPDw84OhES3Nrb3BgUFRcPDw8PDxMU293c3NzdFREREw8PDw8PDw/c29zb3A8TEg8PDw8PDw8PD9bc2dsPDw8PDw8PDw8PDw/U3NjaDw8PDw8PDw8PDw8P09vX2Q8PDw8PDw8PDw8PD9HV1tgPDw8PDw8PDw8PDw8P0dIPDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8P0dIPDw8PDw8PDw8PDw8P0dXW2A8PDw8PDw8PDw8PD9Tc2NoPDw8PDw8PDw8PDw/W3NnbDw8PDw8PDw8PDw/Y29za3A8REg8PDw8PEBLX29zc29sSEBATDw8PODoREtza29wYFBUXDw8PDw8TFNvd3Nzc3RURERMPDw8PDw8P3Nvc29wPExIPDw8PDw8PDw/W3NnbDw8PDw8PDw8PDw8P1NzY2g8PDw8PDw8PDw8PD9HV1tgPDw8PDw8PDw8PDw8P0dIPDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8P0dIPDw8PDw8PDw8PDw8P0dXW2A8PDw8PDw8PDw8P2Nvc2twPERIPDw8PDw8QEtvc3NvbEhAQEw8PDw84OhHc2tvcGBQVFw8PDw8PDxMU3dzc3N0VERETDw8PDw8PD9zb3NvcDxMSDw8PDw8PDw8P0dXW2A8PDw8PDw8PDw8PDw/R0g8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw/R0g8PDw8PDw8PDw8PDw/R1dbYDw8PDw8PDw8PDw8P1NzY2g8PDw8PDw8PDw8PD9bc2dsPDw8PDw8PDw8PD9jb3NrcDxESDw8PDw8QEtfb3Nzb2xIQEBMPDw84OhES3Nrb3BgUFRcPDw8PDxMU293c3NzdFREREw8PDw8PDw/c29zb3A8TEg8PDw8PDw8PD9bc2dsPDw8PDw8PDw8PDw/U3NjaDw8PDw8PDw8PDw8P0dXW2A8PDw8PDw8PDw8PDw/R0g8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PD9HSDw8PDw8PDw8PDw8PD9HW1dgPDw8PDw8PDw8PDw/T19vZDw8PDw8PDw8PDw8P1Njc2g8PDw8PDw8PDw8PD9bZ3NsPDw8PDw8PDw8SEw/c2tzb1w8PDw8PDw8TEREV29vc3NvZEhAPDw8PDxcVFBjc29rcEhE6OQ8PDxMQEBLd3Nzc3dsUEw8PDw8PEhEP3Nvc29wPDw8PDw8PDw8PD9bZ3NsPDw8PDw8PDw8PDw/U2NzaDw8PDw8PDw8PDw8P09fb2Q8PDw8PDw8PDw8PD9HW1dgPDw8PDw8PDw8PDw8P0dIPDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8P0dIPDw8PDw8PDw8PDw8P0dbV2A8PDw8PDw8PDw8PD9TY3NoPDw8PDw8PDw8PDw/W2dzbDw8PDw8PDw8PEhMP3Nrc29cPDw8PDw8PExERFdvb3Nzb2RIQDw8PDw8XFRQY3Nva3BIROjkPDw8TEBAS3dzc3N3bFBMPDw8PDxIRD9zb3NvcDw8PDw8PDw8PDw/W2dzbDw8PDw8PDw8PDw8P1Njc2g8PDw8PDw8PDw8PD9HW1dgPDw8PDw8PDw8PDw8P0dIPDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8P0dIPDw8PDw8PDw8PDw8P0dbV2A8PDw8PDw8PDxITD9za3NvXDw8PDw8PDxMRERXb29zc2xIQDw8PDw8PFxUUGNzb2twROjkPDw8PExAQEt3c3NzdFBMPDw8PDw8SEQ/c29zb3A8PDw8PDw8PDw8P0dbV2A8PDw8PDw8PDw8PDw/R0g8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw/R0g8PDw8PDw8PDw8PDw/R1tXYDw8PDw8PDw8PDw8P1Njc2g8PDw8PDw8PDw8PD9bZ3NsPDw8PDw8PDw8SEw/c2tzb1w8PDw8PDw8TEREV29vc3NvZEhAPDw8PDxcVFBjc29rcEhE6OQ8PDxMQEBLd3Nzc3dsUEw8PDw8PEhEP3Nvc29wPDw8PDw8PDw8PD9bZ3NsPDw8PDw8PDw8PDw/U2NzaDw8PDw8PDw8PDw8P0dbV2A8PDw8PDw8PDw8PDw/R0g8PDw8PDw8PDw8PDw8PDw8PDw8PDw8PDw==', 'base64')] as const;
const shot = [...Buffer.from('AAAAABAQAAAAAAAAAAAAAAAAABAQERMAAAAAAAAAAAAAABAQERISEwAAAAAAAAAAAAAQERISExQAAAAAAAAAAAAQEBESEhMTFAAAAAAAAAAAEBESEhMTExQAAAAAAAAAABAREhITExMUAAAAAAAAAAAAEBESEhMUAAAAAAAAAAAAAAAQERMUAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAQEBAAAAAAAAAAAAAAABAQEBEREQAAAAAAAAAAABAQERESEhIRAAAAAAAAABAQERISEhISEgAAAAAAAAAQERISEhMTEhMAAAAAAAAAABISExMTExMUAAAAAAAAAAAAExQTExMUAAAAAAAAAAAAAAAAFBQUAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAQEBESAAAAAAAAAAAAAAAQEBESExQAAAAAAAAAAAAQEBESEhMTFAAAAAAAAAAAEBESEhMTExQAAAAAAAAAABAREhITExMUAAAAAAAAAAAAEBESExMUAAAAAAAAAAAAABAQERITFAAAAAAAAAAAAAAAEhESFAAAAAAAAAAAAAAAAAATFAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAQEBAAAAAAAAAAAAAAAAAQEBARERIAAAAAAAAAAAAQEBAREhISEwAAAAAAAAAAEBAREhISEhITAAAAAAAAABAREhISExMSFAAAAAAAAAAREhISExMTFAAAAAAAAAAAABMSExMUFAAAAAAAAAAAAAAAFBQUAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA==', 'base64')] as const;

const actor_info = {
  move: 9,
  width: 16,
  height: 16,
  directions: 4,
  frames: 4,
  frame_speed: 8,
  frame_sequence: [0, 1, 2, 3],
  speed: 1,
  size_x: 15,
  size_y: 15,
  strength: 10,
  health: 10,
  num_moves: 1,
  shot_type: 50,
  shot_pattern: 4,
  shots_allowed: 1,
  solid: 0,
  flying: 1,
  rating: 0,
  type: 2,
  // 'EAGLE'
  name: [69, 65, 71, 76, 69, 0, 73, 82, 0],
  func_num: 0,
  func_pass: 0,
  future1: [0, 0, 0, 0, 0, 0],
} as const;

const shot_info = {
  move: 2,
  width: 16,
  height: 16,
  directions: 1,
  frames: 4,
  frame_speed: 3,
  frame_sequence: [0, 1, 2, 3],
  speed: 1,
  size_x: 7,
  size_y: 7,
  strength: 10,
  health: 0,
  num_moves: 2,
  shot_type: 0,
  shot_pattern: 0,
  shots_allowed: 0,
  solid: 0,
  flying: 1,
  rating: 0,
  type: 3,
  // 'EGG'
  name: [69, 71, 71, 0, 0, 0, 0, 0, 0],
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
