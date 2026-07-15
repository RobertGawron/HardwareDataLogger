// ===============================
// Utility: HTTP helper
// ===============================

async function post(url: string, body?: any) {
    await fetch(url, {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: body ? JSON.stringify(body) : undefined,
    });
}

async function getJSON(url: string) {
    const res = await fetch(url);
    return res.json();
}

// ===============================
// DOM Elements
// ===============================

const startBtn = document.getElementById("start-btn") as HTMLButtonElement;
const reloadBtn = document.getElementById("reload-btn") as HTMLButtonElement;
const statusText = document.getElementById("status-text") as HTMLElement;

const speedSlider = document.getElementById("speed-slider") as HTMLInputElement;
const speedValue = document.getElementById("speed-value") as HTMLElement;

const pulseSliders = [
    document.getElementById("pulse-1") as HTMLInputElement,
    document.getElementById("pulse-2") as HTMLInputElement,
    document.getElementById("pulse-3") as HTMLInputElement,
    document.getElementById("pulse-4") as HTMLInputElement,
];

// ===============================
// Simulation State
// ===============================

let isRunning = false;

// ===============================
// Status Handling
// ===============================

async function refreshStatus() {
    const data = await getJSON("/api/status");
    isRunning = data.running;

    if (isRunning) {
        statusText.textContent = "Running";
        statusText.classList.remove("stopped");
        statusText.classList.add("running");
        startBtn.textContent = "Stop";
        startBtn.classList.remove("primary");
        startBtn.classList.add("neutral");
    } else {
        statusText.textContent = "Stopped";
        statusText.classList.remove("running");
        statusText.classList.add("stopped");
        startBtn.textContent = "Start";
        startBtn.classList.remove("neutral");
        startBtn.classList.add("primary");
    }
}

// Poll every second
setInterval(refreshStatus, 1000);

// ===============================
// Start / Stop
// ===============================

startBtn.addEventListener("click", async () => {
    if (isRunning) {
        await post("/api/stop");
    } else {
        await post("/api/start");
    }
    await refreshStatus();
});

// ===============================
// Reload
// ===============================

reloadBtn.addEventListener("click", async () => {
    await post("/api/reload");
});

// ===============================
// Speed Slider
// ===============================

speedSlider.addEventListener("input", async () => {
    const value = parseFloat(speedSlider.value);
    speedValue.textContent = value.toFixed(3) + "s";

    await post("/api/speed", {
        tick_interval: value,
    });
});

// ===============================
// Pulse Sliders
// ===============================

function debounce<T extends (...args: any[]) => void>(
    fn: T,
    delay: number
) {
    let timeout: number;
    return (...args: Parameters<T>) => {
        clearTimeout(timeout);
        timeout = window.setTimeout(() => fn(...args), delay);
    };
}


pulseSliders.forEach((slider, index) => {
    const counterId = index;
    const valueLabel = document.getElementById(
        `pulse-${index + 1}-value`
    ) as HTMLElement;

    const sendUpdate = debounce(async (ppm: number) => {
        await post("/api/pulse", {
            counter_id: counterId,
            pulses_per_minute: ppm,
        });
    }, 150); // 150ms delay

    slider.addEventListener("input", () => {
        const ppm = parseInt(slider.value);
        valueLabel.textContent = ppm.toString();
        sendUpdate(ppm);
    });
});


// ===============================
// HW Buttons 
// ===============================

function bindKeyButton(id: string, keyName: string) {
    const btn = document.getElementById(id) as HTMLButtonElement;

    btn.addEventListener("mousedown", () => {
        post("/api/key/press", { key: keyName });
    });

    btn.addEventListener("mouseup", () => {
        post("/api/key/release", { key: keyName });
    });

    btn.addEventListener("mouseleave", () => {
        post("/api/key/release", { key: keyName });
    });
}

bindKeyButton("btn-up", "UP");
bindKeyButton("btn-down", "DOWN");
bindKeyButton("btn-left", "LEFT");
bindKeyButton("btn-right", "RIGHT");


// ===============================
// Display
// ===============================

async function initDisplay() {
    const canvas = document.getElementById("display-canvas") as HTMLCanvasElement;
    const ctx = canvas.getContext("2d");

    const info = await getJSON("/api/display/info");

    const width = info.width;
    const height = info.height;

    const scale = 2; // visual scaling factor

    canvas.width = width;
    canvas.height = height;

    canvas.style.width = width * scale + "px";
    canvas.style.height = height * scale + "px";

    if (ctx) {
        ctx.imageSmoothingEnabled = false;
    }
}


// ===============================
// Logs
// ===============================


document.querySelectorAll<HTMLButtonElement>(".tab").forEach(tab => {
    tab.addEventListener("click", () => {

        // Remove active from all tabs
        document.querySelectorAll(".tab").forEach(t => 
            t.classList.remove("active")
        );

        // Remove active from all panels
        document.querySelectorAll(".logger-panel").forEach(panel =>
            panel.classList.remove("active")
        );

        // Activate clicked tab
        tab.classList.add("active");

        // Activate corresponding panel
        const targetId = tab.dataset.target!;
        const panel = document.getElementById(targetId);
        panel?.classList.add("active");
    });
});


function appendSdCardRow(event: any) {
    const logBody = document.querySelector("#sdcard .log-body")!;
    const row = document.createElement("div");
    row.className = "log-row";

    const timeCol = document.createElement("div");
    timeCol.className = "col-time";

    // Format UTC nicely
    if (event.timestamp_utc) {
        const date = new Date(event.timestamp_utc);

        if (!isNaN(date.getTime())) {
            timeCol.textContent = date
                .toISOString()
                .replace("T", " ")
                .replace("Z", " UTC");
        } else {
            timeCol.textContent = "Invalid UTC";
        }
    } else {
        timeCol.textContent = "No timestamp";
    }

    const dataCol = document.createElement("div");
    dataCol.className = "col-data";

    switch (event.operation) {
        case "write":
            dataCol.innerHTML =
                `<strong>WRITE</strong> ${event.size} bytes | ` +
                `HEX: ${event.hex.join(" ")} | ` +
                `ASCII: <span class="ascii">${event.ascii.join("")}</span>`;
            break;

        case "open":
            dataCol.textContent =
                `OPEN ${event.filename} (mode=${event.mode})`;
            break;

        case "close":
            dataCol.textContent = "CLOSE";
            break;

        default:
            dataCol.textContent = event.operation.toUpperCase();
    }

    row.appendChild(timeCol);
    row.appendChild(dataCol);
    logBody.appendChild(row);

    logBody.scrollTop = logBody.scrollHeight;
}

type SdCardEvent =
  | { operation: "initialize" }
  | { operation: "start" }
  | { operation: "stop" }
  | { operation: "reset" }
  | { operation: "open"; filename: string; mode: number }
  | { operation: "write"; size: number; data: string }
  | { operation: "close" };

// TODO the port shouldnt be hardcoded.
const sdSocket = new WebSocket("ws://localhost:8080/ws/sdcard");

sdSocket.onmessage = (event) => {
    const data: SdCardEvent = JSON.parse(event.data);
    appendSdCardRow(data);
};


// ===============================
// Init
// ===============================

refreshStatus();
initDisplay();