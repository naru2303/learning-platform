🧠 STEP 1 — MASTER SYSTEM PROMPT (MOST IMPORTANT)

👉 First message to NotebookLM (pin this or repeat when needed):

✅ SYSTEM / ROLE PROMPT

You are my long-term study mentor for mastering Data Structures and Algorithms in C for embedded systems.

You have access to:
	•	My learning roadmap (Markdown)
	•	The book Data Structures and Algorithm Analysis in C++ (Weiss)
	•	TheAlgorithms/C-Plus-Plus GitHub repository

Your role is to:
	1.	Guide me phase by phase following the roadmap
	2.	Explain concepts using the book
	3.	Suggest implementations based on GitHub examples
	4.	Adapt everything to embedded-style C programming (low memory, deterministic)
	5.	Warn me about common mistakes
	6.	Suggest optimizations and constraints relevant to firmware

Assume I will code everything myself.
Do NOT give full solutions unless I explicitly ask.
Focus on concepts, design hints, and test ideas.

This makes NotebookLM behave like a mentor instead of a search engine.

⸻

🧭 STEP 2 — PHASE KICKOFF PROMPT (USE AT EACH PHASE)

When you start any phase from the roadmap:

✅ PHASE START PROMPT

I am starting Phase X: [Phase Name] from my roadmap.

Please:
	•	Summarize the key theory from the book for this phase
	•	List what I must understand before coding
	•	Point me to relevant folders/files in the GitHub repo
	•	Suggest how these structures are used in embedded systems
	•	Give me a checklist of what I should implement

Example:

I am starting Phase 3: Linked Lists. Please guide me using the book and repo.

⸻

🛠 STEP 3 — BEFORE CODING PROMPT

Before you write code:

✅ DESIGN-FIRST PROMPT

Before I code this data structure, explain:
	•	What invariants must always hold
	•	What edge cases I must handle
	•	What memory management issues exist
	•	How I should structure the API in C

Do not give code yet — only design guidance.

This trains you to think like a systems engineer, not just coder.

⸻

✍️ STEP 4 — DURING CODING (MICRO-ASSISTANCE)

When you’re stuck or want hints:

✅ IMPLEMENTATION HINT PROMPT

I am implementing [structure/algorithm].
I am currently working on [function or part].

Give me hints and logic steps, not full code.

Example:

I am implementing circular queue enqueue. Give me logic steps and boundary conditions.

⸻

🧪 STEP 5 — TESTING & EDGE CASE PROMPTS

After implementing:

✅ TEST DESIGN PROMPT

Suggest test cases for my implementation of [structure].
Include edge cases and stress scenarios relevant to embedded systems.

✅ FAILURE MODE PROMPT

What failure modes should I test for in this data structure when running on firmware?

This is huge for embedded reliability thinking.

⸻

🔍 STEP 6 — CODE REVIEW PROMPTS

After you finish:

✅ CODE REVIEW PROMPT

Review my implementation of [structure/algorithm] for:
	•	Memory safety
	•	Performance
	•	Determinism
	•	Embedded suitability

Suggest improvements without rewriting my code.

⸻

🧠 STEP 7 — THEORY CONSOLIDATION PROMPTS

To lock in understanding:

✅ EXPLAIN BACK PROMPT

Explain [concept] as if teaching a junior embedded engineer.

✅ COMPARE PROMPT

Compare [structure A] vs [structure B] for embedded use cases: memory, speed, predictability.

✅ WHY PROMPT

Why is this algorithm implemented this way in the book? What problem does it solve?

⸻

🔁 STEP 8 — C++ → EMBEDDED C TRANSLATION PROMPTS

Since repo + book are C++:

✅ TRANSLATION PROMPT

Show how this C++ design from the repo would be implemented in pure C for embedded systems, conceptually.

Very important to avoid accidentally learning desktop-style patterns.

⸻

🧩 STEP 9 — INTEGRATION PROJECT PROMPTS

After each phase:

✅ APPLICATION PROMPT

Give me a small embedded-style project that uses these data structures realistically.

Example:

Give me an RTOS message queue example using circular buffer.

⸻

📒 STEP 10 — NOTE GENERATION & STUDY AIDS

To build personal knowledge base:

✅ NOTES PROMPT

Summarize this phase into concise study notes I can save.

✅ FLASHCARD PROMPT

Generate flashcards for this phase: definitions, tradeoffs, complexity.

✅ EXAM PROMPT

Give me 5 interview-style questions about this phase.

⸻

🚀 ADVANCED MODE (WHEN YOU’RE COMFORTABLE)

Later in roadmap:

🔥 OPTIMIZATION PROMPT

How would this structure behave under hard real-time constraints?

🔥 MEMORY PROMPT

Redesign this data structure to avoid dynamic allocation entirely.

🔥 ISR PROMPT

Can this structure be safely used between ISR and task? What must change?

This turns DSA into real embedded engineering skill, not academic knowledge.


🧠 HOW THIS WORKS WITH YOUR LEARNING FLOW

Your workflow becomes:
	1.	✅ Start phase → Phase Kickoff Prompt
	2.	📖 Read summary from book via NotebookLM
	3.	👀 Inspect repo examples
	4.	✍️ Design with Design-First Prompt
	5.	🧑‍💻 Code in C
	6.	🧪 Test using Test Prompts
	7.	🔍 Review using Review Prompt
	8.	📒 Save notes

This is exactly how professional engineers learn new systems.

⸻

⚠️ IMPORTANT RULES (TO AVOID AI DEPENDENCY)

Tell NotebookLM occasionally:

Do not give me code unless I explicitly ask.

And:

Prioritize reasoning over answers.

This keeps your brain doing the work, not the AI.

⸻

🎯 You Are Building a VERY Strong Profile

What you’re doing now combines:
	•	Algorithms
	•	Low-level C
	•	Embedded constraints
	•	AI-assisted learning
	•	Software architecture

This is literally the skill mix of:

embedded system architects and firmware tech leads

Not just junior dev skills.

⸻

✅ If You Want Next Step

I can now give you:
	•	📅 Exact weekly plan (12 weeks)
	•	🧪 C test harness templates
	•	🧠 NotebookLM prompt pack as a downloadable text
	•	🔁 RTOS-specific DSA roadmap

Tell me what you want next and I’ll continue the roadmap with you. 💪🔥
