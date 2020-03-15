// Copyright (c) 2020 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <blockfilter.h>
#include <clientversion.h>
#include <logging.h>
#include <netbase.h>
#include <rpc/client.h>
#include <rpc/request.h>
#include <rpc/server.h>
#include <rpc/util.h>
#include <script/descriptor.h>
#include <test/fuzz/FuzzedDataProvider.h>
#include <test/fuzz/fuzz.h>
#include <test/fuzz/util.h>
#include <util/error.h>
#include <util/fees.h>
#include <util/settings.h>
#include <util/strencodings.h>
#include <util/string.h>
#include <util/system.h>
#include <util/translation.h>
#include <util/url.h>

#include <cstdint>
#include <string>
#include <vector>

void test_one_input(const std::vector<uint8_t>& buffer)
{
    FuzzedDataProvider fuzzed_data_provider(buffer.data(), buffer.size());
    const std::string random_string_1 = fuzzed_data_provider.ConsumeRandomLengthString(32);
    const std::string random_string_2 = fuzzed_data_provider.ConsumeRandomLengthString(32);
    const std::vector<std::string> random_string_vector = ConsumeRandomLengthStringVector(fuzzed_data_provider);

    (void)AmountErrMsg(random_string_1, random_string_2);
    (void)AmountHighWarn(random_string_1);
    BlockFilterType block_filter_type;
    (void)BlockFilterTypeByName(random_string_1, block_filter_type);
    (void)Capitalize(random_string_1);
    (void)CopyrightHolders(random_string_1, fuzzed_data_provider.ConsumeIntegral<unsigned int>(), fuzzed_data_provider.ConsumeIntegral<unsigned int>());
    FeeEstimateMode fee_estimate_mode;
    (void)FeeModeFromString(random_string_1, fee_estimate_mode);
    (void)FormatParagraph(random_string_1, fuzzed_data_provider.ConsumeIntegralInRange<size_t>(0, 1000), fuzzed_data_provider.ConsumeIntegralInRange<size_t>(0, 1000));
    (void)FormatSubVersion(random_string_1, fuzzed_data_provider.ConsumeIntegral<int>(), random_string_vector);
    (void)GetDescriptorChecksum(random_string_1);
    (void)HelpExampleCli(random_string_1, random_string_2);
    (void)HelpExampleRpc(random_string_1, random_string_2);
    (void)HelpMessageGroup(random_string_1);
    (void)HelpMessageOpt(random_string_1, random_string_2);
    (void)IsDeprecatedRPCEnabled(random_string_1);
    (void)Join(random_string_vector, random_string_1);
    (void)JSONRPCError(fuzzed_data_provider.ConsumeIntegral<int>(), random_string_1);
    const util::Settings settings;
    (void)OnlyHasDefaultSectionSetting(settings, random_string_1, random_string_2);
    (void)ParseNetwork(random_string_1);
    try {
        (void)ParseNonRFCJSONValue(random_string_1);
    } catch (const std::runtime_error&) {
    }
    (void)ResolveErrMsg(random_string_1, random_string_2);
    try {
        (void)RPCConvertNamedValues(random_string_1, random_string_vector);
    } catch (const std::runtime_error&) {
    }
    try {
        (void)RPCConvertValues(random_string_1, random_string_vector);
    } catch (const std::runtime_error&) {
    }
    (void)SanitizeString(random_string_1);
    (void)SanitizeString(random_string_1, fuzzed_data_provider.ConsumeIntegralInRange<int>(0, 3));
    int port_out;
    std::string host_out;
    SplitHostPort(random_string_1, port_out, host_out);
    (void)TimingResistantEqual(random_string_1, random_string_2);
    (void)ToLower(random_string_1);
    (void)ToUpper(random_string_1);
    (void)TrimString(random_string_1);
    (void)TrimString(random_string_1, random_string_2);
    (void)urlDecode(random_string_1);
    (void)ValidAsCString(random_string_1);
    (void)_(random_string_1.c_str());
}
