/**
 * MIT License
 * Copyright (c) 2023 Grzegorz Grzęda
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "virtual_machine.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VIRTUAL_MACHINE_MAX_COMMAND_COUNT (16)

static struct {
    uint8_t opcode;
    virtual_machine_command_handler handler;
} commands[VIRTUAL_MACHINE_MAX_COMMAND_COUNT];
size_t commands_count = 0;

void register_virtual_machine_command(uint8_t opcode, virtual_machine_command_handler handler)
{
    if (commands_count >= VIRTUAL_MACHINE_MAX_COMMAND_COUNT) {
        return;
    }
    commands[commands_count].opcode = opcode;
    commands[commands_count].handler = handler;
    commands_count++;
}

void run_virtual_machine(uint8_t *program, size_t program_size, uint8_t *data, size_t data_size)
{
    if (!program || !program_size) {
        return;
    }
    virtual_machine_t vm = {
        .program = {.values = program, .size = program_size, .index = 0},
        .data = {.values = data, .size = data_size, .index = 0},
    };
    while (vm.program.index >= program_size) {
        for (size_t index = 0; index < commands_count; index++) {
            if (vm.program.values[vm.program.index] == commands[index].opcode) {
                vm.program.index = commands[index].handler(&vm);
            }
        }
        return;
    }
}