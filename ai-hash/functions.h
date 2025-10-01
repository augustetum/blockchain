#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <vector>
#include <cstdint>
#include <chrono>
#include <fstream>
#include <limits>
#include <filesystem>

std::string pasirinktiFaila();
std::string failoNuskaitymas();

class CustomHash {
private:
    // Magic constants for mixing (derived from golden ratio and other mathematical constants)
    static constexpr uint64_t K1 = 0x9E3779B97F4A7C15ULL;
    static constexpr uint64_t K2 = 0xBF58476D1CE4E5B9ULL;
    static constexpr uint64_t K3 = 0x94D049BB133111EBULL;
    static constexpr uint64_t K4 = 0xC4CEB9FE1A85EC53ULL;
    
    // Rotation function for better bit mixing
    static uint64_t rotateLeft(uint64_t value, int shift) {
        return (value << shift) | (value >> (64 - shift));
    }
    
    // Mix function for avalanche effect
    static uint64_t mix(uint64_t value) {
        value ^= value >> 33;
        value *= K1;
        value ^= value >> 33;
        value *= K2;
        value ^= value >> 33;
        return value;
    }
    
    // Process 8-byte chunks
    static uint64_t processChunk(uint64_t chunk, uint64_t& state1, uint64_t& state2, uint64_t& state3, uint64_t& state4) {
        chunk *= K1;
        chunk = rotateLeft(chunk, 31);
        chunk *= K2;
        
        state1 ^= chunk;
        state1 = rotateLeft(state1, 27);
        state1 += state2;
        state1 = state1 * 5 + 0x52DCE729;
        
        // Update other states for better mixing
        state2 = rotateLeft(state2 ^ chunk, 31) * K3;
        state3 += chunk * K4;
        state4 ^= rotateLeft(chunk, 17);
        
        return state1;
    }

public:
    // Main hash function - returns 256-bit hash as hex string (64 characters)
    static std::string hash(const std::string& input) {
        const uint8_t* data = reinterpret_cast<const uint8_t*>(input.c_str());
        size_t length = input.length();
        
        // Initialize states with different constants
        uint64_t state1 = K1;
        uint64_t state2 = K2;
        uint64_t state3 = K3;
        uint64_t state4 = K4;
        
        // Add length to initial state for length sensitivity
        state1 += length;
        state2 ^= length << 32;
        state3 += rotateLeft(length, 16);
        state4 ^= length * K1;
        
        // Process 8-byte chunks
        size_t chunks = length / 8;
        for (size_t i = 0; i < chunks; i++) {
            uint64_t chunk = 0;
            for (int j = 0; j < 8; j++) {
                chunk |= static_cast<uint64_t>(data[i * 8 + j]) << (j * 8);
            }
            processChunk(chunk, state1, state2, state3, state4);
        }
        
        // Process remaining bytes
        size_t remaining = length % 8;
        if (remaining > 0) {
            uint64_t lastChunk = 0;
            for (size_t i = 0; i < remaining; i++) {
                lastChunk |= static_cast<uint64_t>(data[chunks * 8 + i]) << (i * 8);
            }
            // Add padding bit to distinguish different lengths
            lastChunk |= static_cast<uint64_t>(0x80) << (remaining * 8);
            processChunk(lastChunk, state1, state2, state3, state4);
        }
        
        // Final mixing for avalanche effect
        state1 = mix(state1 ^ state2 ^ state3 ^ state4);
        state2 = mix(state2 ^ state3 ^ state4 ^ state1);
        state3 = mix(state3 ^ state4 ^ state1 ^ state2);
        state4 = mix(state4 ^ state1 ^ state2 ^ state3);
        
        // Additional rounds of mixing
        for (int round = 0; round < 3; round++) {
            uint64_t temp = state1;
            state1 = mix(state1 ^ rotateLeft(state2, 13));
            state2 = mix(state2 ^ rotateLeft(state3, 17));
            state3 = mix(state3 ^ rotateLeft(state4, 19));
            state4 = mix(state4 ^ rotateLeft(temp, 23));
        }
        
        // Convert to hex string (64 characters = 256 bits)
        std::stringstream ss;
        ss << std::hex << std::setfill('0');
        ss << std::setw(16) << state1;
        ss << std::setw(16) << state2;
        ss << std::setw(16) << state3;
        ss << std::setw(16) << state4;
        
        return ss.str();
    }
};