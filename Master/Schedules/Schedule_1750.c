schedule_length = 101;
sf[1] = tsch_schedule_get_slotframe_by_handle(1);
if (sf[1]){
    tsch_schedule_remove_slotframe(sf[1]);
}
sf[1] = tsch_schedule_add_slotframe(1, schedule_length);
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
sf[6] = tsch_schedule_get_slotframe_by_handle(6);
if (sf[6]){
    tsch_schedule_remove_slotframe(sf[6]);
}
sf[6] = tsch_schedule_add_slotframe(6, schedule_length);
sender_of_flow[1] = 6;
receiver_of_flow[1] = 17;
sender_of_flow[2] = 16;
receiver_of_flow[2] = 10;
sender_of_flow[3] = 2;
receiver_of_flow[3] = 21;
sender_of_flow[4] = 8;
receiver_of_flow[4] = 20;
sender_of_flow[5] = 18;
receiver_of_flow[5] = 4;
sender_of_flow[6] = 9;
receiver_of_flow[6] = 1;
hash_map_insert(&last_received_relayed_packet_of_flow, 1, 0);
hash_map_insert(&last_received_relayed_packet_of_flow, 2, 0);
hash_map_insert(&last_received_relayed_packet_of_flow, 3, 0);
hash_map_insert(&last_received_relayed_packet_of_flow, 4, 0);
hash_map_insert(&last_received_relayed_packet_of_flow, 5, 0);
hash_map_insert(&last_received_relayed_packet_of_flow, 6, 0);
#if TSCH_TTL_BASED_RETRANSMISSIONS
first_tx_slot_in_flow[0] = 7;
last_tx_slot_in_flow[0] = 29;
first_tx_slot_in_flow[1] = 18;
last_tx_slot_in_flow[1] = 29;
first_tx_slot_in_flow[2] = 22;
last_tx_slot_in_flow[2] = 29;
first_tx_slot_in_flow[3] = 18;
last_tx_slot_in_flow[3] = 29;
first_tx_slot_in_flow[4] = 11;
last_tx_slot_in_flow[4] = 28;
first_tx_slot_in_flow[5] = 0;
last_tx_slot_in_flow[5] = 18;
#endif /* TSCH_TTL_BASED_RETRANSMISSIONS */
if (node_id == 9){
    own_transmission_flow = 6;
    is_sender = 1;
    own_receiver = 1;
    const scheduled_link_t add_link[] = {
        { 6, 1, 0, 0 },
        { 6, 1, 1, 0 },
        { 6, 1, 2, 0 },
        { 6, 1, 3, 0 },
        { 6, 1, 4, 0 },
        { 6, 1, 5, 0 },
        { 6, 1, 6, 0 },
    };
    hash_map_insert(&forward_to, 6, 7);
    const uint8_t cha_idx[] = {0, };
    const uint8_t cha_idx_to[] = {7, };
    add_links(add_link, 7, cha_idx, cha_idx_to, 1);
    destination.u8[NODE_ID_INDEX] = 8;
    tsch_queue_update_time_source(&destination);
    #if !TSCH_TTL_BASED_RETRANSMISSIONS
        sending_slots[0] = 0;
        sending_slots[1] = 1;
        sending_slots[2] = 2;
        sending_slots[3] = 3;
        sending_slots[4] = 4;
        sending_slots[5] = 5;
        sending_slots[6] = 6;
        num_sending_slots = 7;
    #endif /* !TSCH_TTL_BASED_RETRANSMISSIONS */
} else if (node_id == 7){
    const scheduled_link_t add_link[] = {
        { 6, 3, 1, 0 },
        { 6, 3, 2, 0 },
        { 6, 3, 3, 0 },
        { 6, 3, 4, 0 },
        { 6, 3, 5, 0 },
        { 6, 3, 6, 0 },
        { 6, 1, 18, 2 },
        { 5, 3, 12, 1 },
        { 5, 3, 13, 1 },
        { 5, 3, 14, 1 },
        { 5, 3, 15, 1 },
        { 5, 3, 16, 1 },
        { 5, 3, 17, 1 },
        { 5, 1, 28, 3 },
        { 6, 2, 0, 0 },
        { 5, 2, 11, 1 },
    };
    hash_map_insert(&forward_to, 6, 1);
    hash_map_insert(&forward_to, 5, 4);
    const uint8_t cha_idx[] = {0, 7, 14, 15, };
    const uint8_t cha_idx_to[] = {1, 4, 9, 18, };
    add_links(add_link, 16, cha_idx, cha_idx_to, 4);
    destination.u8[NODE_ID_INDEX] = 8;
    tsch_queue_update_time_source(&destination);
} else if (node_id == 1){
    const scheduled_link_t add_link[] = {
        { 1, 2, 7, 0 },
        { 4, 2, 19, 1 },
        { 6, 2, 1, 0 },
        { 6, 2, 2, 0 },
        { 6, 2, 3, 0 },
        { 6, 2, 4, 0 },
        { 6, 2, 5, 0 },
        { 6, 2, 6, 0 },
        { 6, 2, 18, 2 },
        { 1, 3, 8, 0 },
        { 1, 3, 9, 0 },
        { 1, 3, 10, 0 },
        { 1, 3, 11, 0 },
        { 1, 3, 12, 0 },
        { 1, 3, 13, 0 },
        { 1, 3, 14, 0 },
        { 1, 3, 15, 0 },
        { 1, 3, 16, 0 },
        { 1, 1, 17, 0 },
        { 4, 3, 20, 1 },
        { 4, 3, 21, 1 },
        { 4, 3, 22, 1 },
        { 4, 3, 23, 1 },
        { 4, 3, 24, 1 },
        { 4, 3, 25, 1 },
        { 4, 3, 26, 1 },
        { 4, 3, 27, 1 },
        { 4, 3, 28, 1 },
        { 4, 1, 29, 1 },
    };
    hash_map_insert(&forward_to, 1, 15);
    hash_map_insert(&forward_to, 4, 20);
    const uint8_t cha_idx[] = {0, 2, 9, 19, };
    const uint8_t cha_idx_to[] = {6, 7, 15, 20, };
    add_links(add_link, 29, cha_idx, cha_idx_to, 4);
    destination.u8[NODE_ID_INDEX] = 4;
    tsch_queue_update_time_source(&destination);
} else if (node_id == 6){
    own_transmission_flow = 1;
    is_sender = 1;
    own_receiver = 17;
    const scheduled_link_t add_link[] = {
        { 1, 1, 7, 0 },
        { 1, 1, 8, 0 },
        { 1, 1, 9, 0 },
        { 1, 1, 10, 0 },
        { 1, 1, 11, 0 },
        { 1, 1, 12, 0 },
        { 1, 1, 13, 0 },
        { 1, 1, 14, 0 },
        { 1, 1, 15, 0 },
        { 1, 1, 16, 0 },
        { 4, 3, 19, 1 },
        { 4, 3, 20, 1 },
        { 4, 3, 21, 1 },
        { 4, 3, 22, 1 },
        { 4, 3, 23, 1 },
        { 4, 3, 24, 1 },
        { 4, 3, 25, 1 },
        { 4, 3, 26, 1 },
        { 4, 3, 27, 1 },
        { 4, 1, 28, 1 },
        { 4, 2, 18, 1 },
    };
    hash_map_insert(&forward_to, 1, 1);
    hash_map_insert(&forward_to, 4, 1);
    const uint8_t cha_idx[] = {0, 20, };
    const uint8_t cha_idx_to[] = {1, 8, };
    add_links(add_link, 21, cha_idx, cha_idx_to, 2);
    destination.u8[NODE_ID_INDEX] = 8;
    tsch_queue_update_time_source(&destination);
    #if !TSCH_TTL_BASED_RETRANSMISSIONS
        sending_slots[0] = 7;
        sending_slots[1] = 8;
        sending_slots[2] = 9;
        sending_slots[3] = 10;
        sending_slots[4] = 11;
        sending_slots[5] = 12;
        sending_slots[6] = 13;
        sending_slots[7] = 14;
        sending_slots[8] = 15;
        sending_slots[9] = 16;
        num_sending_slots = 10;
    #endif /* !TSCH_TTL_BASED_RETRANSMISSIONS */
} else if (node_id == 15){
    const scheduled_link_t add_link[] = {
        { 1, 2, 8, 0 },
        { 2, 2, 18, 0 },
        { 1, 3, 9, 0 },
        { 1, 3, 10, 0 },
        { 1, 3, 11, 0 },
        { 1, 3, 12, 0 },
        { 1, 3, 13, 0 },
        { 1, 3, 14, 0 },
        { 1, 3, 15, 0 },
        { 1, 3, 16, 0 },
        { 1, 3, 17, 0 },
        { 1, 1, 29, 2 },
        { 2, 3, 19, 0 },
        { 2, 3, 20, 0 },
        { 2, 3, 21, 0 },
        { 2, 3, 22, 0 },
        { 2, 3, 23, 0 },
        { 2, 3, 24, 0 },
        { 2, 3, 25, 0 },
        { 2, 3, 26, 0 },
        { 2, 3, 27, 0 },
        { 2, 1, 28, 0 },
    };
    hash_map_insert(&forward_to, 1, 17);
    hash_map_insert(&forward_to, 2, 18);
    const uint8_t cha_idx[] = {0, 1, 2, 12, };
    const uint8_t cha_idx_to[] = {1, 16, 17, 18, };
    add_links(add_link, 22, cha_idx, cha_idx_to, 4);
    destination.u8[NODE_ID_INDEX] = 18;
    tsch_queue_update_time_source(&destination);
} else if (node_id == 17){
    const scheduled_link_t add_link[] = {
        { 1, 2, 9, 0 },
        { 1, 2, 10, 0 },
        { 1, 2, 11, 0 },
        { 1, 2, 12, 0 },
        { 1, 2, 13, 0 },
        { 1, 2, 14, 0 },
        { 1, 2, 15, 0 },
        { 1, 2, 16, 0 },
        { 1, 2, 17, 0 },
        { 1, 2, 29, 2 },
    };
    const uint8_t cha_idx[] = {0, };
    const uint8_t cha_idx_to[] = {15, };
    add_links(add_link, 10, cha_idx, cha_idx_to, 1);
    destination.u8[NODE_ID_INDEX] = 15;
    tsch_queue_update_time_source(&destination);
} else if (node_id == 18){
    own_transmission_flow = 5;
    is_sender = 1;
    own_receiver = 4;
    const scheduled_link_t add_link[] = {
        { 5, 1, 11, 1 },
        { 5, 1, 12, 1 },
        { 5, 1, 13, 1 },
        { 5, 1, 14, 1 },
        { 5, 1, 15, 1 },
        { 5, 1, 16, 1 },
        { 5, 1, 17, 1 },
        { 2, 3, 20, 0 },
        { 2, 3, 21, 0 },
        { 2, 3, 22, 0 },
        { 2, 3, 23, 0 },
        { 2, 3, 24, 0 },
        { 2, 3, 25, 0 },
        { 2, 3, 26, 0 },
        { 2, 3, 27, 0 },
        { 2, 3, 28, 0 },
        { 2, 1, 29, 0 },
        { 2, 2, 19, 0 },
    };
    hash_map_insert(&forward_to, 5, 7);
    hash_map_insert(&forward_to, 2, 10);
    const uint8_t cha_idx[] = {0, 7, 17, };
    const uint8_t cha_idx_to[] = {7, 10, 15, };
    add_links(add_link, 18, cha_idx, cha_idx_to, 3);
    destination.u8[NODE_ID_INDEX] = 8;
    tsch_queue_update_time_source(&destination);
    #if !TSCH_TTL_BASED_RETRANSMISSIONS
        sending_slots[0] = 11;
        sending_slots[1] = 12;
        sending_slots[2] = 13;
        sending_slots[3] = 14;
        sending_slots[4] = 15;
        sending_slots[5] = 16;
        sending_slots[6] = 17;
        num_sending_slots = 7;
    #endif /* !TSCH_TTL_BASED_RETRANSMISSIONS */
} else if (node_id == 4){
    const scheduled_link_t add_link[] = {
        { 5, 2, 12, 1 },
        { 5, 2, 13, 1 },
        { 5, 2, 14, 1 },
        { 5, 2, 15, 1 },
        { 5, 2, 16, 1 },
        { 5, 2, 17, 1 },
        { 5, 2, 28, 3 },
    };
    const uint8_t cha_idx[] = {0, };
    const uint8_t cha_idx_to[] = {7, };
    add_links(add_link, 7, cha_idx, cha_idx_to, 1);
    destination.u8[NODE_ID_INDEX] = 8;
    tsch_queue_update_time_source(&destination);
} else if (node_id == 16){
    own_transmission_flow = 2;
    is_sender = 1;
    own_receiver = 10;
    const scheduled_link_t add_link[] = {
        { 2, 1, 18, 0 },
        { 2, 1, 19, 0 },
        { 2, 1, 20, 0 },
        { 2, 1, 21, 0 },
        { 2, 1, 22, 0 },
        { 2, 1, 23, 0 },
        { 2, 1, 24, 0 },
        { 2, 1, 25, 0 },
        { 2, 1, 26, 0 },
        { 2, 1, 27, 0 },
    };
    hash_map_insert(&forward_to, 2, 15);
    const uint8_t cha_idx[] = {0, };
    const uint8_t cha_idx_to[] = {15, };
    add_links(add_link, 10, cha_idx, cha_idx_to, 1);
    destination.u8[NODE_ID_INDEX] = 1;
    tsch_queue_update_time_source(&destination);
    #if !TSCH_TTL_BASED_RETRANSMISSIONS
        sending_slots[0] = 18;
        sending_slots[1] = 19;
        sending_slots[2] = 20;
        sending_slots[3] = 21;
        sending_slots[4] = 22;
        sending_slots[5] = 23;
        sending_slots[6] = 24;
        sending_slots[7] = 25;
        sending_slots[8] = 26;
        sending_slots[9] = 27;
        num_sending_slots = 10;
    #endif /* !TSCH_TTL_BASED_RETRANSMISSIONS */
} else if (node_id == 8){
    own_transmission_flow = 4;
    is_sender = 1;
    own_receiver = 20;
    const scheduled_link_t add_link[] = {
        { 4, 1, 18, 1 },
        { 4, 1, 19, 1 },
        { 4, 1, 20, 1 },
        { 4, 1, 21, 1 },
        { 4, 1, 22, 1 },
        { 4, 1, 23, 1 },
        { 4, 1, 24, 1 },
        { 4, 1, 25, 1 },
        { 4, 1, 26, 1 },
        { 4, 1, 27, 1 },
    };
    hash_map_insert(&forward_to, 4, 6);
    const uint8_t cha_idx[] = {0, };
    const uint8_t cha_idx_to[] = {6, };
    add_links(add_link, 10, cha_idx, cha_idx_to, 1);
    #if !TSCH_TTL_BASED_RETRANSMISSIONS
        sending_slots[0] = 18;
        sending_slots[1] = 19;
        sending_slots[2] = 20;
        sending_slots[3] = 21;
        sending_slots[4] = 22;
        sending_slots[5] = 23;
        sending_slots[6] = 24;
        sending_slots[7] = 25;
        sending_slots[8] = 26;
        sending_slots[9] = 27;
        num_sending_slots = 10;
    #endif /* !TSCH_TTL_BASED_RETRANSMISSIONS */
} else if (node_id == 10){
    const scheduled_link_t add_link[] = {
        { 2, 2, 20, 0 },
        { 2, 2, 21, 0 },
        { 2, 2, 22, 0 },
        { 2, 2, 23, 0 },
        { 2, 2, 24, 0 },
        { 2, 2, 25, 0 },
        { 2, 2, 26, 0 },
        { 2, 2, 27, 0 },
        { 2, 2, 28, 0 },
        { 2, 2, 29, 0 },
    };
    const uint8_t cha_idx[] = {0, };
    const uint8_t cha_idx_to[] = {18, };
    add_links(add_link, 10, cha_idx, cha_idx_to, 1);
    destination.u8[NODE_ID_INDEX] = 8;
    tsch_queue_update_time_source(&destination);
} else if (node_id == 20){
    const scheduled_link_t add_link[] = {
        { 4, 2, 20, 1 },
        { 4, 2, 21, 1 },
        { 4, 2, 22, 1 },
        { 4, 2, 23, 1 },
        { 4, 2, 24, 1 },
        { 4, 2, 25, 1 },
        { 4, 2, 26, 1 },
        { 4, 2, 27, 1 },
        { 4, 2, 28, 1 },
        { 4, 2, 29, 1 },
    };
    const uint8_t cha_idx[] = {0, };
    const uint8_t cha_idx_to[] = {1, };
    add_links(add_link, 10, cha_idx, cha_idx_to, 1);
    destination.u8[NODE_ID_INDEX] = 1;
    tsch_queue_update_time_source(&destination);
} else if (node_id == 2){
    own_transmission_flow = 3;
    is_sender = 1;
    own_receiver = 21;
    const scheduled_link_t add_link[] = {
        { 3, 1, 22, 2 },
        { 3, 1, 23, 2 },
        { 3, 1, 24, 2 },
        { 3, 1, 25, 2 },
        { 3, 1, 26, 2 },
        { 3, 1, 27, 2 },
        { 3, 1, 28, 2 },
    };
    hash_map_insert(&forward_to, 3, 3);
    const uint8_t cha_idx[] = {0, };
    const uint8_t cha_idx_to[] = {3, };
    add_links(add_link, 7, cha_idx, cha_idx_to, 1);
    destination.u8[NODE_ID_INDEX] = 7;
    tsch_queue_update_time_source(&destination);
    #if !TSCH_TTL_BASED_RETRANSMISSIONS
        sending_slots[0] = 22;
        sending_slots[1] = 23;
        sending_slots[2] = 24;
        sending_slots[3] = 25;
        sending_slots[4] = 26;
        sending_slots[5] = 27;
        sending_slots[6] = 28;
        num_sending_slots = 7;
    #endif /* !TSCH_TTL_BASED_RETRANSMISSIONS */
} else if (node_id == 3){
    const scheduled_link_t add_link[] = {
        { 3, 2, 22, 2 },
        { 3, 3, 23, 2 },
        { 3, 3, 24, 2 },
        { 3, 3, 25, 2 },
        { 3, 3, 26, 2 },
        { 3, 3, 27, 2 },
        { 3, 3, 28, 2 },
        { 3, 1, 29, 3 },
    };
    hash_map_insert(&forward_to, 3, 21);
    const uint8_t cha_idx[] = {0, 1, };
    const uint8_t cha_idx_to[] = {2, 21, };
    add_links(add_link, 8, cha_idx, cha_idx_to, 2);
    destination.u8[NODE_ID_INDEX] = 6;
    tsch_queue_update_time_source(&destination);
} else if (node_id == 21){
    const scheduled_link_t add_link[] = {
        { 3, 2, 23, 2 },
        { 3, 2, 24, 2 },
        { 3, 2, 25, 2 },
        { 3, 2, 26, 2 },
        { 3, 2, 27, 2 },
        { 3, 2, 28, 2 },
        { 3, 2, 29, 3 },
    };
    const uint8_t cha_idx[] = {0, };
    const uint8_t cha_idx_to[] = {3, };
    add_links(add_link, 7, cha_idx, cha_idx_to, 1);
    destination.u8[NODE_ID_INDEX] = 8;
    tsch_queue_update_time_source(&destination);
} else if (node_id == 5){
    destination.u8[NODE_ID_INDEX] = 12;
    tsch_queue_update_time_source(&destination);
} else if (node_id == 12){
    destination.u8[NODE_ID_INDEX] = 8;
    tsch_queue_update_time_source(&destination);
} else if (node_id == 13){
    destination.u8[NODE_ID_INDEX] = 21;
    tsch_queue_update_time_source(&destination);
} else if (node_id == 14){
    destination.u8[NODE_ID_INDEX] = 5;
    tsch_queue_update_time_source(&destination);
} else if (node_id == 19){
    destination.u8[NODE_ID_INDEX] = 21;
    tsch_queue_update_time_source(&destination);
}
    max_transmissions[1] = 10;
    max_transmissions[3] = 10;
    max_transmissions[0] = 10;
    max_transmissions[2] = 7;
    max_transmissions[5] = 7;
    max_transmissions[4] = 7;
