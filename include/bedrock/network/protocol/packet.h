// Copyright (c) 2024, The Endstone Project. (https://endstone.dev) All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once
#include "bedrock/network/network_peer.h"
#include "bedrock/network/protocol/compressibility.h"
#include "bedrock/network/protocol/sub_client_id.h"
#include "bedrock/network/raknet/packet_priority.h"
class Packet {
public:
    virtual ~Packet() = default;

private:
    PacketPriority priority_;                          // + 8
    NetworkPeer::Reliability reliability_;             // + 12
    SubClientId sub_client_id_;                        // + 16
    bool is_handled_;                                  // + 17
    NetworkPeer::PacketRecvTimepoint recv_timepoint_;  // + 24
    void *handler_;                                    // + 32
    Compressibility compressibility_;                  // + 40
};
BEDROCK_STATIC_ASSERT_SIZE(Packet, 48, 48);
