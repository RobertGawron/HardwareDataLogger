FROM ubuntu:20.04

# Non-interactive for apt commands
ENV DEBIAN_FRONTEND=noninteractive

# Install dependencies
RUN apt-get update && apt-get install -y \
    wget curl gnupg2 software-properties-common apt-transport-https ca-certificates \
    supervisor \
    && rm -rf /var/lib/apt/lists/*

# ---------------------
# Install InfluxDB
# ---------------------
# Add InfluxDB repository
RUN wget -qO- https://repos.influxdata.com/influxdata-archive_compat.key | apt-key add - && \
    echo "deb https://repos.influxdata.com/debian bullseye stable" | tee /etc/apt/sources.list.d/influxdb.list && \
    apt-get update && apt-get install -y influxdb && \
    rm -rf /var/lib/apt/lists/*

# ---------------------
# Install Grafana
# ---------------------
# Add Grafana GPG key and repository
RUN wget -q -O /usr/share/keyrings/grafana.key https://packages.grafana.com/gpg.key && \
    echo "deb [signed-by=/usr/share/keyrings/grafana.key] https://packages.grafana.com/oss/deb stable main" \
    | tee /etc/apt/sources.list.d/grafana.list && \
    apt-get update && apt-get install -y grafana && \
    rm -rf /var/lib/apt/lists/*

# Configure InfluxDB (basic)
RUN mkdir -p /var/lib/influxdb && \
    chown influxdb:influxdb /var/lib/influxdb && \
    sed -i 's/# store-enabled = true/store-enabled = true/' /etc/influxdb/influxdb.conf

# Configure Grafana (defaults)
RUN mkdir -p /var/lib/grafana && \
    chown grafana:grafana /var/lib/grafana

# ---------------------
# Supervisor configuration
# ---------------------
# Create a supervisor config that runs both InfluxDB and Grafana
RUN mkdir -p /etc/supervisor/conf.d

# Create supervisor config file
COPY ./DevOps/Pi/supervisord.conf /etc/supervisor/conf.d/supervisord.conf
RUN apt-get update && apt-get install -y dos2unix
RUN dos2unix "/etc/supervisor/conf.d/supervisord.conf"


EXPOSE 3000 8086



# By default, influxd will listen on 8086 and grafana on 3000
CMD ["/usr/bin/supervisord", "-c", "/etc/supervisor/conf.d/supervisord.conf"]
