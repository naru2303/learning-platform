# AI-Engineering Workflow Strategy: The "Second Brain" and "Skill" Framework

This document outlines a professional automation framework for software engineers, based on the methodologies used by John Kim to eliminate "contextual maintenance" and automate non-coding overhead.

---

## 1. Core Philosophy: Context is King
Traditional AI usage involves "shallow" memory where engineers repeatedly re-explain architecture and decisions, which is not true automation but "moving work around". 
*   **Context over Prompting:** Great automation depends on high-quality data/context rather than perfect prompt wording. 
*   **The Onboarding Parallel:** Treat the AI like a junior engineer: onboard it once with deep project context so it can work autonomously moving forward.
*   **Context Compaction:** Use local `.md` files to create a "small compaction of context" or "vectorized memory" so the AI doesn't have to parse the entire codebase for every task.

---

## 2. The Infrastructure: The "Second Brain"
The "Second Brain" is a local, persistent knowledge base that allows domain knowledge to compound over time.

### **Setup and Components**
*   **Initialization:** Use Claude Code to create a project knowledge base stored in local `.md` files.
*   **Living Documentation:** The brain must contain:
    *   Project history and the "shape" of the codebase.
    *   Logical reasoning behind architectural decisions.
    *   Relevant code pointers and "gatekeeping" configuration files.
    *   An internal, AI-managed **To-Do List** for the project.

### **The "Update" Ritual**
*   **The 30-Second Sync:** After every working session, prompt Claude: **"Update what we just did to my project"**.
*   **Benefit:** This ensures the AI stays synchronized with daily progress, making it more valuable the more you use it.

---

## 3. The Automation Mechanism: "Skills"
A "Skill" is a saved workflow—a set of steps written by Claude as a "giant prompt" in a markdown file that can be executed consistently.

### **How to Build a Skill**
1.  **Manual Execution:** Perform the task manually with Claude once, step-by-step.
2.  **Codification:** Prompt Claude: **"Turn what we did into a skill"**.
3.  **Execution:** Trigger the skill in future sessions; Claude will look up fresh context from the Second Brain and execute the steps in your preferred style.

---

## 4. Key Engineering Workflows (Examples)

### **A. Atomic PR Splitting**
*   **The "Chicken Scratch" Method:** First, build the entire feature quickly and "messily" to ensure it works.
*   **The Split Logic:** Once the feature is complete, use a Skill to split the large diff into "bite-sizable," landable chunks.
*   **Ordering:** The AI follows a specific logical order: **Interfaces → Helper Methods → Integration → Tests** (starting with leaf nodes and moving to integration).

### **B. SEV (Severity) & On-Call Investigation**
*   **Bisecting the Branch:** Prompt the AI to run a deep dive on the latest release branch.
*   **Theory Generation:** The AI looks at every commit/PR in the log to provide theories on what broke based on the SEV description.
*   **Scaling:** Run **multiple simultaneous Claude sessions** to investigate different tasks or theories to save hours of manual bisecting.

### **C. Ship Announcements & Documentation**
*   **Standardized Structure:** Automate the writing of "ship" posts using the following template:
    1.  What changed?
    2.  How to test it?
    3.  What to watch out for?
    4.  How to give feedback.
*   **Status Reports:** Generate reports using the internal AI-managed to-do list and recent session history without re-explaining the work.

### **D. Interactive Diff Review**
*   **Line-by-Line Conversation:** A skill where Claude walks through a diff with the engineer line-by-line to ensure quality before submission.

---

## 5. Expert Enhancements for Plan Generation
*The following suggestions are provided by the AI Expert persona to enhance the YouTuber's framework for your planning agent:*

*   **Skill: "Contextual Onboarding":** A skill that generates a high-level summary for a specific module based on the Second Brain, specifically for when you return to old code.
*   **Skill: "Architecture Guardrail":** A pre-commit skill where Claude checks if new "chicken scratch" code violates architectural decisions recorded in the Second Brain.
*   **Skill: "Cross-Tool Sync":** Integration via **MCP (Model Context Protocol)** to sync the internal AI to-do list with external trackers like Jira or GitHub Issues.