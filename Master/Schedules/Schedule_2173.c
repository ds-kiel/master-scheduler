schedule_length = 101;
sf[2] = tsch_schedule_get_slotframe_by_handle(2);
if (sf[2]){
  tsch_schedule_remove_slotframe(sf[2]);
}
sf[2] = tsch_schedule_add_slotframe(2, schedule_length);
sf[3] = tsch_schedule_get_slotframe_by_handle(3);
if (sf[3]){
  tsch_schedule_remove_slotframe(sf[3]);
}
sf[3] = tsch_schedule_add_slotframe(3, schedule_length);
sf[4] = tsch_schedule_get_slotframe_by_handle(4);
if (sf[4]){
  tsch_schedule_remove_slotframe(sf[4]);
}
sf[4] = tsch_schedule_add_slotframe(4, schedule_length);
sf[5] = tsch_schedule_get_slotframe_by_handle(5);
if (sf[5]){
  tsch_schedule_remove_slotframe(sf[5]);
}
sf[5] = tsch_schedule_add_slotframe(5, schedule_length);
sf[1] = tsch_schedule_get_slotframe_by_handle(1);
if (sf[1]){
  tsch_schedule_remove_slotframe(sf[1]);
}
sf[1] = tsch_schedule_add_slotframe(1, schedule_length);
sf[6] = tsch_schedule_get_slotframe_by_handle(6);
if (sf[6]){
  tsch_schedule_remove_slotframe(sf[6]);
}
sf[6] = tsch_schedule_add_slotframe(6, schedule_length);
hash_map_insert(&last_received_relayed_packet_of_flow, 2, 0);
hash_map_insert(&last_received_relayed_packet_of_flow, 3, 0);
hash_map_insert(&last_received_relayed_packet_of_flow, 4, 0);
hash_map_insert(&last_received_relayed_packet_of_flow, 5, 0);
hash_map_insert(&last_received_relayed_packet_of_flow, 1, 0);
hash_map_insert(&last_received_relayed_packet_of_flow, 6, 0);
sender_of_flow[2] = 16;
receiver_of_flow[2] = 10;
sender_of_flow[3] = 2;
receiver_of_flow[3] = 21;
sender_of_flow[4] = 8;
receiver_of_flow[4] = 20;
sender_of_flow[5] = 18;
receiver_of_flow[5] = 4;
sender_of_flow[1] = 6;
receiver_of_flow[1] = 17;
sender_of_flow[6] = 9;
receiver_of_flow[6] = 1;
#if TSCH_TTL_BASED_RETRANSMISSIONS
  first_tx_slot_in_flow[1] = 6;
  last_tx_slot_in_flow[1] = 9;
  first_tx_slot_in_flow[2] = 3;
  last_tx_slot_in_flow[2] = 6;
  first_tx_slot_in_flow[3] = 1;
  last_tx_slot_in_flow[3] = 4;
  first_tx_slot_in_flow[4] = 0;
  last_tx_slot_in_flow[4] = 9;
  first_tx_slot_in_flow[0] = 7;
  last_tx_slot_in_flow[0] = 9;
  first_tx_slot_in_flow[5] = 5;
  last_tx_slot_in_flow[5] = 9;
#endif /* TSCH_TTL_BASED_RETRANSMISSIONS */
if (node_id == 18){
  own_transmission_flow = 5;
  is_sender = 1;
  own_receiver = 4;
  const scheduled_link_t add_link[] = {
    {  5,  1,  0,  0 },
    {  5,  1,  7,  1 },
    {  5,  1,  8,  1 },
  };
  hash_map_insert(&forward_to, 5, 8);
  const uint8_t cha_idx[] = {0, };
  const uint8_t cha_idx_to[] = {8, };
  add_links(add_link, 3, cha_idx, cha_idx_to, 1);
  destination.u8[NODE_ID_INDEX] = 8;
  tsch_queue_update_time_source(&destination);
  max_transmissions[4] = 3;
  #if !TSCH_TTL_BASED_RETRANSMISSIONS
    sending_slots[0] = 0;
    sending_slots[1] = 7;
    sending_slots[2] = 8;
    num_sending_slots = 3;
  #endif /* !TSCH_TTL_BASED_RETRANSMISSIONS */
} else if (node_id == 8){
  own_transmission_flow = 4;
  is_sender = 1;
  own_receiver = 20;
  const scheduled_link_t add_link[] = {
    {  5,  3,  7,  1 },
    {  5,  3,  8,  1 },
    {  5,  1,  9,  1 },
    {  3,  2,  4,  0 },
    {  5,  2,  0,  0 },
    {  4,  1,  1,  0 },
    {  4,  1,  2,  0 },
    {  4,  1,  3,  1 },
    {  3,  3,  5,  0 },
    {  3,  1,  6,  1 },
  };
  hash_map_insert(&forward_to, 5, 4);
  hash_map_insert(&forward_to, 4, 21);
  hash_map_insert(&forward_to, 3, 21);
  const uint8_t cha_idx[] = {0, 3, 4, 5, };
  const uint8_t cha_idx_to[] = {4, 6, 18, 21, };
  add_links(add_link, 10, cha_idx, cha_idx_to, 4);
  max_transmissions[4] = 3;
  max_transmissions[3] = 3;
  max_transmissions[2] = 2;
  #if !TSCH_TTL_BASED_RETRANSMISSIONS
    sending_slots[0] = 1;
    sending_slots[1] = 2;
    sending_slots[2] = 3;
    num_sending_slots = 3;
  #endif /* !TSCH_TTL_BASED_RETRANSMISSIONS */
} else if (node_id == 21){
  const scheduled_link_t add_link[] = {
    {  4,  2,  1,  0 },
    {  3,  2,  5,  0 },
    {  3,  2,  6,  1 },
    {  2,  3,  8,  0 },
    {  2,  1,  9,  0 },
    {  2,  2,  7,  0 },
    {  4,  3,  2,  0 },
    {  4,  3,  3,  1 },
    {  4,  1,  4,  1 },
  };
  hash_map_insert(&forward_to, 2, 10);
  hash_map_insert(&forward_to, 4, 20);
  const uint8_t cha_idx[] = {0, 3, 5, 6, };
  const uint8_t cha_idx_to[] = {8, 10, 15, 20, };
  add_links(add_link, 9, cha_idx, cha_idx_to, 4);
  destination.u8[NODE_ID_INDEX] = 8;
  tsch_queue_update_time_source(&destination);
  max_transmissions[1] = 2;
  max_transmissions[3] = 3;
} else if (node_id == 20){
  const scheduled_link_t add_link[] = {
    {  4,  2,  2,  0 },
    {  4,  2,  3,  1 },
    {  4,  2,  4,  1 },
  };
  const uint8_t cha_idx[] = {0, };
  const uint8_t cha_idx_to[] = {21, };
  add_links(add_link, 3, cha_idx, cha_idx_to, 1);
  destination.u8[NODE_ID_INDEX] = 21;
  tsch_queue_update_time_source(&destination);
} else if (node_id == 2){
  own_transmission_flow = 3;
  is_sender = 1;
  own_receiver = 21;
  const scheduled_link_t add_link[] = {
    {  3,  1,  3,  0 },
    {  3,  1,  4,  0 },
  };
  hash_map_insert(&forward_to, 3, 6);
  const uint8_t cha_idx[] = {0, };
  const uint8_t cha_idx_to[] = {6, };
  add_links(add_link, 2, cha_idx, cha_idx_to, 1);
  destination.u8[NODE_ID_INDEX] = 6;
  tsch_queue_update_time_source(&destination);
  max_transmissions[2] = 2;
  #if !TSCH_TTL_BASED_RETRANSMISSIONS
    sending_slots[0] = 3;
    sending_slots[1] = 4;
    num_sending_slots = 2;
  #endif /* !TSCH_TTL_BASED_RETRANSMISSIONS */
} else if (node_id == 6){
  own_transmission_flow = 1;
  is_sender = 1;
  own_receiver = 17;
  const scheduled_link_t add_link[] = {
    {  3,  2,  3,  0 },
    {  3,  3,  4,  0 },
    {  3,  1,  5,  0 },
    {  1,  1,  7,  2 },
  };
  hash_map_insert(&forward_to, 3, 8);
  hash_map_insert(&forward_to, 1, 12);
  const uint8_t cha_idx[] = {0, 1, 3, };
  const uint8_t cha_idx_to[] = {2, 8, 12, };
  add_links(add_link, 4, cha_idx, cha_idx_to, 3);
  destination.u8[NODE_ID_INDEX] = 8;
  tsch_queue_update_time_source(&destination);
  max_transmissions[2] = 2;
  max_transmissions[0] = 1;
  #if !TSCH_TTL_BASED_RETRANSMISSIONS
    sending_slots[0] = 7;
    num_sending_slots = 1;
  #endif /* !TSCH_TTL_BASED_RETRANSMISSIONS */
} else if (node_id == 9){
  own_transmission_flow = 6;
  is_sender = 1;
  own_receiver = 1;
  const scheduled_link_t add_link[] = {
    {  6,  1,  5,  1 },
    {  6,  1,  6,  2 },
  };
  hash_map_insert(&forward_to, 6, 12);
  const uint8_t cha_idx[] = {0, };
  const uint8_t cha_idx_to[] = {12, };
  add_links(add_link, 2, cha_idx, cha_idx_to, 1);
  destination.u8[NODE_ID_INDEX] = 8;
  tsch_queue_update_time_source(&destination);
  max_transmissions[5] = 2;
  #if !TSCH_TTL_BASED_RETRANSMISSIONS
    sending_slots[0] = 5;
    sending_slots[1] = 6;
    num_sending_slots = 2;
  #endif /* !TSCH_TTL_BASED_RETRANSMISSIONS */
} else if (node_id == 12){
  const scheduled_link_t add_link[] = {
    {  6,  3,  6,  2 },
    {  6,  1,  9,  3 },
    {  1,  1,  8,  2 },
    {  1,  2,  7,  2 },
    {  6,  2,  5,  1 },
  };
  hash_map_insert(&forward_to, 6, 1);
  hash_map_insert(&forward_to, 1, 5);
  const uint8_t cha_idx[] = {0, 2, 3, 4, };
  const uint8_t cha_idx_to[] = {1, 5, 6, 9, };
  add_links(add_link, 5, cha_idx, cha_idx_to, 4);
  destination.u8[NODE_ID_INDEX] = 8;
  tsch_queue_update_time_source(&destination);
  max_transmissions[5] = 2;
  max_transmissions[0] = 1;
} else if (node_id == 16){
  own_transmission_flow = 2;
  is_sender = 1;
  own_receiver = 10;
  const scheduled_link_t add_link[] = {
    {  2,  1,  6,  0 },
    {  2,  1,  7,  0 },
  };
  hash_map_insert(&forward_to, 2, 15);
  const uint8_t cha_idx[] = {0, };
  const uint8_t cha_idx_to[] = {15, };
  add_links(add_link, 2, cha_idx, cha_idx_to, 1);
  destination.u8[NODE_ID_INDEX] = 15;
  tsch_queue_update_time_source(&destination);
  max_transmissions[1] = 2;
  #if !TSCH_TTL_BASED_RETRANSMISSIONS
    sending_slots[0] = 6;
    sending_slots[1] = 7;
    num_sending_slots = 2;
  #endif /* !TSCH_TTL_BASED_RETRANSMISSIONS */
} else if (node_id == 15){
  const scheduled_link_t add_link[] = {
    {  2,  2,  6,  0 },
    {  2,  3,  7,  0 },
    {  2,  1,  8,  0 },
  };
  hash_map_insert(&forward_to, 2, 21);
  const uint8_t cha_idx[] = {0, 1, };
  const uint8_t cha_idx_to[] = {16, 21, };
  add_links(add_link, 3, cha_idx, cha_idx_to, 2);
  destination.u8[NODE_ID_INDEX] = 21;
  tsch_queue_update_time_source(&destination);
  max_transmissions[1] = 2;
} else if (node_id == 1){
  const scheduled_link_t add_link[] = {
    {  6,  2,  6,  2 },
    {  6,  2,  9,  3 },
  };
  const uint8_t cha_idx[] = {0, };
  const uint8_t cha_idx_to[] = {12, };
  add_links(add_link, 2, cha_idx, cha_idx_to, 1);
  destination.u8[NODE_ID_INDEX] = 4;
  tsch_queue_update_time_source(&destination);
} else if (node_id == 4){
  const scheduled_link_t add_link[] = {
    {  5,  2,  7,  1 },
    {  5,  2,  8,  1 },
    {  5,  2,  9,  1 },
  };
  const uint8_t cha_idx[] = {0, };
  const uint8_t cha_idx_to[] = {8, };
  add_links(add_link, 3, cha_idx, cha_idx_to, 1);
  destination.u8[NODE_ID_INDEX] = 8;
  tsch_queue_update_time_source(&destination);
} else if (node_id == 10){
  const scheduled_link_t add_link[] = {
    {  2,  2,  8,  0 },
    {  2,  2,  9,  0 },
  };
  const uint8_t cha_idx[] = {0, };
  const uint8_t cha_idx_to[] = {21, };
  add_links(add_link, 2, cha_idx, cha_idx_to, 1);
  destination.u8[NODE_ID_INDEX] = 8;
  tsch_queue_update_time_source(&destination);
} else if (node_id == 5){
  const scheduled_link_t add_link[] = {
    {  1,  2,  8,  2 },
    {  1,  1,  9,  2 },
  };
  hash_map_insert(&forward_to, 1, 17);
  const uint8_t cha_idx[] = {0, 1, };
  const uint8_t cha_idx_to[] = {12, 17, };
  add_links(add_link, 2, cha_idx, cha_idx_to, 2);
  destination.u8[NODE_ID_INDEX] = 12;
  tsch_queue_update_time_source(&destination);
  max_transmissions[0] = 1;
} else if (node_id == 17){
  const scheduled_link_t add_link[] = {
    {  1,  2,  9,  2 },
  };
  const uint8_t cha_idx[] = {0, };
  const uint8_t cha_idx_to[] = {5, };
  add_links(add_link, 1, cha_idx, cha_idx_to, 1);
  destination.u8[NODE_ID_INDEX] = 15;
  tsch_queue_update_time_source(&destination);
} else if (node_id == 19){
  destination.u8[NODE_ID_INDEX] = 10;
  tsch_queue_update_time_source(&destination);
} else if (node_id == 3){
  destination.u8[NODE_ID_INDEX] = 6;
  tsch_queue_update_time_source(&destination);
} else if (node_id == 14){
  destination.u8[NODE_ID_INDEX] = 21;
  tsch_queue_update_time_source(&destination);
} else if (node_id == 7){
  destination.u8[NODE_ID_INDEX] = 8;
  tsch_queue_update_time_source(&destination);
}
tsch_schedule_add_link(sf[1], LINK_OPTION_TX | LINK_OPTION_RX, LINK_TYPE_ADVERTISING_ONLY, &tsch_broadcast_address, 100, 0);
