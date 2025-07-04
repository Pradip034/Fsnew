// agent.js

const fs = require('fs').promises; // Using promises version of fs for async operations
const path = require('path');

// --- Configuration ---
// IMPORTANT: In a real application, you would manage API keys securely (e.g., environment variables).
// For this example, we leave it empty. The Canvas environment will inject it if needed for gemini-2.0-flash.
const API_KEY = ""; // Leave this empty for gemini-2.0-flash in Canvas environment
const GEMINI_API_URL = `https://generativelanguage.googleapis.com/v1beta/models/gemini-2.0-flash:generateContent?key=${API_KEY}`;
const MEDICAL_REPORT_FILE = 'medical_report.txt';

/**
 * Reads the content of a specified file.
 * @param {string} filePath - The path to the file to read.
 * @returns {Promise<string>} A promise that resolves with the file content as a string.
 */
async function readMedicalReport(filePath) {
    try {
        console.log(`Reading medical report from: ${filePath}`);
        const content = await fs.readFile(filePath, 'utf8');
        console.log("Medical report read successfully.");
        return content;
    } catch (error) {
        console.error(`Error reading medical report file: ${error.message}`);
        throw error;
    }
}

/**
 * Sends a prompt with the medical report content to the Gemini API
 * and returns the extracted information.
 * @param {string} reportText - The full text of the medical report.
 * @returns {Promise<object>} A promise that resolves with the parsed JSON response from the LLM.
 */
async function processReportWithAI(reportText) {
    console.log("Sending medical report to AI for processing...");

    const prompt = `
        You are a highly accurate medical information extractor.
        Your task is to analyze the following medical report and extract the key information.
        Return the information as a JSON object with the following keys:
        - "patientName": Full name of the patient.
        - "dateOfReport": The date the report was issued (format YYYY-MM-DD).
        - "diagnosis": The primary diagnosis.
        - "medications": An array of medications prescribed or mentioned.
        - "doctorName": The name of the attending physician.
        - "findings": A brief summary of key findings.

        If any piece of information is not found, use "N/A" for strings, or an empty array for lists.

        Medical Report:
        ---START REPORT---
        ${reportText}
        ---END REPORT---
    `;

    const chatHistory = [];
    chatHistory.push({ role: "user", parts: [{ text: prompt }] });

    const payload = {
        contents: chatHistory,
        generationConfig: {
            responseMimeType: "application/json",
            responseSchema: {
                type: "OBJECT",
                properties: {
                    "patientName": { "type": "STRING" },
                    "dateOfReport": { "type": "STRING" },
                    "diagnosis": { "type": "STRING" },
                    "medications": {
                        "type": "ARRAY",
                        "items": { "type": "STRING" }
                    },
                    "doctorName": { "type": "STRING" },
                    "findings": { "type": "STRING" }
                },
                required: ["patientName", "dateOfReport", "diagnosis", "medications", "doctorName", "findings"]
            }
        }
    };

    try {
        const response = await fetch(GEMINI_API_URL, {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify(payload)
        });

        if (!response.ok) {
            const errorText = await response.text();
            throw new Error(`API request failed with status ${response.status}: ${errorText}`);
        }

        const result = await response.json();

        if (result.candidates && result.candidates.length > 0 &&
            result.candidates[0].content && result.candidates[0].content.parts &&
            result.candidates[0].content.parts.length > 0) {
            const jsonString = result.candidates[0].content.parts[0].text;
            console.log("AI response received. Attempting to parse JSON...");
            return JSON.parse(jsonString);
        } else {
            console.warn("Unexpected API response structure:", result);
            throw new Error("Could not extract content from AI response.");
        }
    } catch (error) {
        console.error(`Error processing report with AI: ${error.message}`);
        throw error;
    }
}

/**
 * Main function to run the AI agent.
 */
async function main() {
    const reportFilePath = path.join(__dirname, MEDICAL_REPORT_FILE);

    try {
        const reportContent = await readMedicalReport(reportFilePath);
        const extractedData = await processReportWithAI(reportContent);

        console.log("\n--- Extracted Medical Information ---");
        console.log(JSON.stringify(extractedData, null, 2)); // Pretty print JSON

        // You can now use the extractedData object for further processing,
        // e.g., storing in a database, displaying in a UI, etc.

    } catch (error) {
        console.error("\nAI Agent failed:", error.message);
    }
}

// Run the main function
main();
