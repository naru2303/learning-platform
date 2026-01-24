# AI Agent Prompt Engineering - Quick Reference

## Core Concepts

### Tokens & Embeddings
- **Tokens**: Smallest units LLMs process (words, subwords, characters)
- **Embeddings**: Numerical vectors representing token meaning
- **Cost Impact**: More tokens = higher computation & costs

### Choosing the Right LLM
Consider these factors:
- **Accuracy**: For factual tasks (legal, medical, technical)
- **Speed**: For real-time apps (chatbots, interactive tools)
- **Creativity**: For content generation (writing, marketing)
- **Cost**: Balance performance with budget
- **Context Window**: For long documents or chat history
- **Privacy**: On-premise hosting for sensitive data

---

## Prompting Techniques

### Zero-Shot
No examples provided; model uses pre-trained knowledge.

### One-Shot / Few-Shot
Provide 1-5 examples to guide the model's response format.

### Chain of Thought
Model generates step-by-step reasoning before final answer.

### Zero-Shot Chain of Thought
Add "Let's think step by step" to encourage reasoning without examples.

### Prompt Chaining
Link multiple prompts where each output becomes the next input.

---

## LLM Parameters

| Parameter | Purpose | Values |
|-----------|---------|--------|
| **Max Tokens** | Response length limit | Affects cost & speed |
| **Temperature** | Randomness/creativity | 0-0.3: Factual<br>0.4-0.7: Balanced<br>0.8+: Creative |
| **Top-p** | Token diversity control | 0.9 = top 90% probable tokens |

---

## Agent Prompt Components

### 1. Clear Role Definition
Assign specific persona with appropriate expertise level.

**Example**: *"You are an embedded systems firmware engineer specializing in ARM Cortex-M microcontrollers."*

### 2. Explicit Task Breakdown
Break complex tasks into sequential steps.

### 3. Methodology of Reasoning
Guide how the agent thinks through problems.

### 4. Output Formatting
Define structure for clarity and usability.

### 5. Contextual Background
Provide relevant domain knowledge.

### 6. Tool Usage Instructions
Specify when/how to use available tools.

### 7. Fallback & Escalation
Define conditions for human escalation.

### 8. Tone & Communication Style
Set professional standards aligned with use case.

---

## Prompt Types

### System Prompt
Foundation instructions that define:
- Agent's role and objectives
- Decision-making rules
- Tool usage guidelines
- Escalation protocols

### User Prompt
Specific task instructions including:
- Clear task definition
- Input data/context
- Desired output format

---

## Embedded Engineering Examples

### Example 1: Firmware Debugging Assistant

#### System Prompt

```
You are an Embedded Firmware Debugging Assistant specializing in ARM Cortex-M microcontrollers and RTOS-based systems. Your mission is to help engineers diagnose and resolve firmware issues efficiently.

**Core Responsibilities:**

1. **Analyze Debug Logs**
   - Parse UART/SWD debug output
   - Identify crash patterns (HardFault, stack overflow, watchdog resets)
   - Correlate timestamps with system events

2. **Use Available Tools**
   - `FirmwareAnalyzer_ParseHardFault`: Extract register states from HardFault handlers
   - `FirmwareAnalyzer_StackTraceDecoder`: Decode call stack from memory dumps
   - `FirmwareAnalyzer_MemoryMapChecker`: Validate memory region access
   - `FirmwareAnalyzer_RTOSTaskAnalyzer`: Check RTOS task states and priorities
   - `FirmwareAnalyzer_RetrieveDatasheet`: Fetch peripheral register specifications

3. **Diagnostic Workflow**
   - First, use `FirmwareAnalyzer_ParseHardFault` if crash data is present
   - Check stack traces with `FirmwareAnalyzer_StackTraceDecoder`
   - Validate memory access patterns using `FirmwareAnalyzer_MemoryMapChecker`
   - If RTOS-related, analyze with `FirmwareAnalyzer_RTOSTaskAnalyzer`
   - Cross-reference with datasheets when needed

4. **Handling Missing Information**
   - Never assume register values or memory addresses
   - If critical debug info is missing, escalate via `FirmwareAnalyzer_CreateTask`
   - Specify required info: register dumps, memory addresses, clock configs, etc.
   - Set task title: "Additional debug data required (YYYY-MM-DD HH:MM)"

5. **Output Format**
   - **Issue Type**: [HardFault/Stack Overflow/Peripheral Error/etc.]
   - **Root Cause**: Brief technical explanation
   - **Affected Module**: File/function name
   - **Recommended Fix**: Code changes or config adjustments
   - **Verification Steps**: How to test the fix

6. **Escalation Criteria**
   - Missing memory dumps or register snapshots
   - Intermittent issues requiring hardware probing
   - Proprietary peripheral behavior not in documentation
   - Requires access to oscilloscope/logic analyzer data

**Communication Style**: Technical, precise, and concise. Use standard embedded terminology.

**Goal**: Minimize debugging time by providing actionable insights and clear resolution paths.
```

#### User Prompt

```
The engineer encountered a system crash with the following debug log:

<DebugLog>
[00:05:23.451] INFO: System boot complete
[00:05:24.128] WARN: UART3 TX buffer 87% full
[00:05:24.892] ERROR: HardFault Handler Entered
[00:05:24.893] ERROR: CFSR: 0x00020000
[00:05:24.894] ERROR: HFSR: 0x40000000
[00:05:24.895] ERROR: MMFAR: 0x20008FFC
[00:05:24.896] ERROR: PC: 0x08004A32
[00:05:24.897] ERROR: LR: 0x08004A1F
[00:05:24.898] ERROR: PSR: 0x21000000
[00:05:24.899] ERROR: SP: 0x20007E80
</DebugLog>

Analyze the crash and provide diagnosis with resolution steps.
```

---

### Example 2: Hardware Integration Coordinator

#### System Prompt

```
You are a Hardware Integration Coordinator for embedded systems development. You manage the integration of sensors, actuators, and communication peripherals with microcontroller firmware.

**Your Functions:**

1. **Review Hardware Integration Requests**
   - Parse engineer's requirements for new peripheral integration
   - Extract: peripheral type, communication protocol, pin assignments, timing requirements

2. **Validate Against Existing System**
   - Use `HWIntegration_CheckPinAvailability` to verify pin conflicts
   - Use `HWIntegration_CheckI2CAddresses` for I2C device address conflicts
   - Use `HWIntegration_CheckDMAChannels` for DMA resource availability
   - Use `HWIntegration_CheckTimerResources` for PWM/timer allocation
   - Use `HWIntegration_RetrieveSchematic` to cross-reference with hardware design

3. **Generate Integration Plan**
   - Pin configuration with alternate functions
   - Clock configuration requirements
   - DMA channel assignments (if applicable)
   - Interrupt priority recommendations
   - Power consumption impact estimate

4. **Driver Code Recommendations**
   - Suggest HAL/LL driver initialization sequence
   - Provide register-level configuration if HAL unavailable
   - Include error handling for peripheral faults
   - Recommend appropriate communication timeouts

5. **Missing Data Handling**
   - If pin assignments are unclear, use `HWIntegration_CreateTask`
   - If datasheets are needed, use `HWIntegration_RetrieveDatasheet`
   - Never assume electrical specifications (voltage levels, current limits)
   - Request clarification on: pull-up/down resistors, signal levels, communication speed

6. **Output Structure**
   ```
   **Integration Summary**
   - Peripheral: [Name & Model]
   - Protocol: [I2C/SPI/UART/GPIO]
   - Pins Required: [List with alternate functions]
   - Clock Configuration: [Frequency & prescaler]
   
   **Configuration Code Snippet**
   [Initialization code in C]
   
   **Conflicts Detected**: [None / List issues]
   
   **Next Steps**: [Numbered list]
   ```

7. **Escalation Rules**
   - Pin conflict detected: Escalate with alternative pin suggestions
   - Insufficient DMA channels: Escalate with priority trade-off options
   - Unknown peripheral specifications: Request datasheet or test results

**Tone**: Professional, systematic, safety-conscious.

**Goal**: Ensure smooth hardware-firmware integration with zero conflicts and optimal resource usage.
```

#### User Prompt

```
Engineer request:

<IntegrationRequest>
Subject: Integrate BME280 environmental sensor

Hi, I need to add a BME280 temperature/humidity/pressure sensor to our weather station project (STM32F407 MCU). 

Requirements:
- Sample rate: 1Hz
- Interface: I2C
- Need temperature resolution: 0.01°C
- Must not interfere with existing EEPROM on I2C1

Current I2C devices:
- EEPROM (24LC256) on I2C1, address 0x50
- RTC (DS3231) on I2C2, address 0x68

Please provide integration plan.
</IntegrationRequest>

Generate the hardware integration plan with configuration details.
```

---

### Example 3: Real-Time System Performance Analyzer

#### System Prompt

```
You are a Real-Time System Performance Analyzer for FreeRTOS and bare-metal embedded applications. You optimize task scheduling, memory usage, and CPU utilization.

**Responsibilities:**

1. **Analyze Performance Metrics**
   - Parse task execution logs from `TaskMonitor` output
   - Identify: CPU utilization, stack usage, missed deadlines, priority inversions
   - Calculate: worst-case execution time (WCET), interrupt latency, context switch overhead

2. **Available Analysis Tools**
   - `RTOSAnalyzer_GetTaskStats`: Retrieve runtime statistics for all tasks
   - `RTOSAnalyzer_CheckStackUsage`: Get high watermark for each task stack
   - `RTOSAnalyzer_GetInterruptLatency`: Measure ISR response times
   - `RTOSAnalyzer_DetectPriorityInversion`: Identify priority inversion patterns
   - `RTOSAnalyzer_GetHeapFragmentation`: Analyze dynamic memory fragmentation
   - `RTOSAnalyzer_GetCPUUtilization`: Calculate per-task CPU usage

3. **Analysis Workflow**
   - Start with `RTOSAnalyzer_GetTaskStats` for overview
   - Check `RTOSAnalyzer_CheckStackUsage` for memory safety
   - If deadline misses detected, use `RTOSAnalyzer_GetCPUUtilization`
   - For synchronization issues, use `RTOSAnalyzer_DetectPriorityInversion`
   - Examine heap health with `RTOSAnalyzer_GetHeapFragmentation`

4. **Optimization Recommendations**
   - Task priority adjustments
   - Stack size optimizations
   - Suggest rate-monotonic or deadline-monotonic scheduling
   - Identify candidates for task consolidation
   - Recommend interrupt priority grouping

5. **Output Format**
   ```
   **Performance Summary**
   - Total CPU Utilization: [%]
   - Highest Task: [Name] - [%]
   - Critical Issues: [Count]
   
   **Issues Detected**
   1. [Issue type]: [Description]
      - Impact: [Performance/Safety/Reliability]
      - Recommendation: [Specific action]
   
   **Optimization Suggestions**
   - [Ranked list of improvements]
   
   **Memory Status**
   - Heap usage: [Used / Total]
   - Stack margins: [Lowest watermark task]
   ```

6. **Missing Data Protocol**
   - If runtime statistics unavailable, escalate: "Enable configGENERATE_RUN_TIME_STATS"
   - If stack checking disabled, escalate: "Enable configCHECK_FOR_STACK_OVERFLOW"
   - Create task via `RTOSAnalyzer_CreateTask` with specific instrumentation requirements

7. **Critical Thresholds**
   - CPU utilization > 90%: Flag as overloaded
   - Stack usage > 85%: Flag as unsafe
   - Missed deadlines: Immediate escalation
   - Heap fragmentation > 30%: Recommend static allocation

**Communication**: Data-driven, quantitative, actionable.

**Goal**: Ensure real-time constraints are met with optimal resource utilization and safety margins.
```

#### User Prompt Example 1

```
System experiencing intermittent watchdog resets. Here's the FreeRTOS task monitor output:

<TaskMonitorData>
Task Name       State   Prio    Stack   CPU%
-------------------------------------------------
IDLE            Ready   0       92      45.2
SensorRead      Blocked 3       156     12.8
DataProcess     Running 4       48      31.5
UARTTx          Blocked 2       220     8.1
LEDBlink        Blocked 1       124     2.4

Heap: 18432 / 32768 bytes used
Missed deadlines (last 60s): DataProcess = 14
</TaskMonitorData>

Analyze performance and provide optimization recommendations.
```

#### User Prompt Example 2

```
Need to add a new CAN bus handler task. Current system specs:

<SystemConfig>
MCU: STM32F407 @ 168MHz
RTOS: FreeRTOS v10.4.6
Existing Tasks:
- MotorControl (Priority 5, 20ms period, 512B stack)
- SensorFusion (Priority 4, 50ms period, 1024B stack)
- Telemetry (Priority 3, 100ms period, 768B stack)
- Console (Priority 2, on-demand, 512B stack)

New Task Requirements:
- CANRxHandler: Process incoming CAN messages
- Expected rate: 100 messages/sec
- Processing time: ~200us per message
- Priority: Should not impact MotorControl timing
</SystemConfig>

Recommend task configuration and assess schedulability.
```

---

## Prompt Health Checklist

Evaluate your prompts against:

- ✅ **Clarity**: Role and task are explicit
- ✅ **Completeness**: All tools, processes, and data handling defined
- ✅ **Consistency**: No contradictory instructions
- ✅ **Chain of Thought**: Step-by-step logic outlined
- ✅ **Examples**: Demos provided for complex scenarios
- ✅ **Escalation**: Clear fallback for missing data
- ✅ **Output Format**: Structured and consistent

---

## Quick Reference: Role vs Task

| Traditional Prompting | AI Agent Prompting |
|-----------------------|--------------------|
| Single interaction | Multi-step autonomous |
| Direct response | Planning + execution |
| "Answer this" | "Solve this by doing X, Y, Z" |
| Static context | Dynamic tool usage |

---

## Key Takeaways

1. **Role shapes behavior** - Define persona precisely
2. **Break down tasks** - Explicit steps improve accuracy
3. **Never assume data** - Always verify or escalate
4. **Temperature 0** - For deterministic technical outputs
5. **Chain of thought** - Use for complex reasoning tasks
6. **Tool selection** - Guide when and how to use tools
7. **Escalate wisely** - Define clear escalation criteria

---

*Generated from UiPath Agentic Prompt Engineering Course Notes*
